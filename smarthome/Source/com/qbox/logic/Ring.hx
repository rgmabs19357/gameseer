package com.qbox.logic;

import haxe.io.Bytes;


class Ring{

    public var _heads:Array<RingNode>;
    public var _nodeIndex:Int;
    //public var _isRingSetup:Bool;
    public var _count:Int;
    public var _cbRingSetup:Dynamic->Void;
    public var _cb753Setup:Dynamic->Void;


    //only support ring out port 1 or ring out port 2 currently
    public function new( index:Int){
        _heads = new Array<RingNode>();
        _nodeIndex = index;
        //_isRingSetup = false;
        _count = 0;
    }

    public function getRingNodeIfRingAvailable(c:Channel, wnd:Wnd ):Array<RingNode>{
        var rns = new Array<RingNode>();
        for ( i in _heads){
            //trace( "test");
            var n = i;
            while (n !=null ){
                rns.push( n);
                n = n._next[_nodeIndex];
                if ( n == i){
                    break;
                }
            }
        }

        for ( n in rns){
            var out:String = null;
            if ( c._screen == n._screen){
                out = c._inport;
            }else{
                out = n._inport[_nodeIndex];
            }
            var p:Wnd = n._screen._ringports.get(out);
            if ( p != null && p != wnd){
                return null;
            }
        }
        return rns;
    }

    public function setupRing(c:Channel, wnd:Wnd, cb:Dynamic->Void):Bool{
        if ( _count > 0) {trace("_count:"+_count);return false;}
        if ( _cbRingSetup != null) { trace("_cbRingSetup not null!");return false;}

        var isSucceed= true;
        var rns = getRingNodeIfRingAvailable( c, wnd);
        if ( rns != null){
            _cbRingSetup = cb;
            _count += rns.length;
            for ( n in rns){
                trace( "set ring of qbox: "+ n._screen._ipv4);
                if ( c._screen == n._screen){
                    if( n._screen.setRingChannel( n._outport[_nodeIndex], c._inport, cbSetupRing, wnd)){
                        isSucceed = false;
                    }else{ cbSetupRing(null,null); }
                }else{
                    if(n._screen.setRingChannel( n._outport[_nodeIndex], n._inport[_nodeIndex], cbSetupRing, wnd)){
                        isSucceed = false;
                    }else{ cbSetupRing(null,null); }
                }
            }
        }
        return false;
    }

    function cbSetupRing( args:Dynamic, s:Screen){
        if ( args!= null && args.get("error") == "1") {
            trace("there is a error occurred at qbox: "+ s._ipv4);
            var tmp = _cbRingSetup;
            tmp("error");
            _cbRingSetup = null;
            return;
        }
        --_count;
        if (_count == 0){
            var tmp = _cbRingSetup;
            _cbRingSetup = null;
            tmp(null);
        }
    }

    public function setup753( wnd:Wnd, ss:Array<Screen>, c:Channel,  cb:Dynamic->Void):Bool{
        if ( _count > 0) {trace("_count:"+_count);return false ;}
        if ( _cb753Setup!= null) { trace("_cb753Setup not null!");return false;}

        for ( i in ss){
            if ( isInRing(i) == false )  {
                trace("not in ring: "+ i._ipv4);
                return false;
            }
            if ( !i.has753Available() && i.get753Port(wnd) ==null ){
                trace("not 753 available: "+ i._ipv4);
                return false;
            }
        }

        _cb753Setup= cb;
        _count += ss.length;
        for (i in ss){
            //var p = i.get753Port(wnd);
            if ( i == c._screen){
                //if ( p == null ){
                    i.set753Channel( c._inport, cbSetup753, wnd);
                    trace("screen "+i._ipv4 +" set up 753 to channel port: "+c._inport);
                    //}else{
                    //trace("screen "+i._ipv4 +" already set up 753 to channel port: "+c._inport);
                    //cbSetup753(null, null);
                    //}
            }else{
                //if ( p == null  ){
                    i.set753Channel( i._ringNode._inport[_nodeIndex] , cbSetup753, wnd);
                    trace("screen "+i._ipv4 +" set up 753 to in port: "+i._ringNode._inport[_nodeIndex]);
                    //}else{
                    //trace("screen "+i._ipv4 +" already set up 753 to in port: "+i._ringNode._inport[_nodeIndex]);
                    //cbSetup753(null, null);
                    //}
            }
        }
        return true;
    }

    function cbSetup753( args:Dynamic, s:Screen){
        if ( args != null && args.get("error") == "1") {
            trace("there is a error occurred at qbox: "+ s._ipv4);
            _cb753Setup("error");
            return;
        }

        --_count;
        if (_count == 0){
            var tmp = _cb753Setup;
            _cb753Setup= null;
            tmp(null);
        }
    }
    public function getScreens( c:Channel):Array<Screen>{
        var ss = new Array<Screen>();
        for ( i in _heads){
            var n = i;
            var circlePoint:RingNode =  null;
            while ( n != circlePoint){
                if ( n._screen == c._screen){
                    circlePoint = n;
                }
                if ( circlePoint != null) ss.push(i._screen);
                n = n._next[_nodeIndex];
                if ( n == i && circlePoint == null ) break;
            }
        }
        return ss;
    }

    public function isHead( rn:RingNode){
        for ( i in _heads){
            if (rn == i){
                return true;
            }
        }
        return false;
    }

    public function getRingHead( col:Int, row:Int):RingNode{
        for ( i in _heads){
            if ( col == i._col && row == i._row){
                return i;
            }
        }
        return null;
    }

    public function isInRing( s:Screen):Bool{
        if ( _heads.length == 0 ) return false;
        //trace(_heads.length);
        for ( rn in _heads){
            var n = rn;
            while (n !=null ){
                //trace("ring"+n._col+n._row+n._screen._ipv4);
                if ( n._screen == s){
                    return true;
                }
                n = n._next[_nodeIndex];
                if ( n == rn){
                    break;
                }
            }
        }
        //trace("done");
        return false;
    }

    public function newHead( rn:RingNode){
        //trace( rn._col);
        //trace( rn._row);
        var tmp = rn._pre[_nodeIndex];
        while(tmp != rn){
            if ( tmp == null){ tmp = rn;break; }
            tmp = tmp._pre[_nodeIndex];
        }
        eatHead( tmp);
        _heads.push( tmp);
        //trace( _heads.length);
    }

    public function eatHead( rn:RingNode){
        var ate = new Array<RingNode>();
        for ( i in _heads){
            var next = rn;
            while( next != null ){
                if ( i == next){
                    ate.push(i);
                    break;
                }
                next = next._next[_nodeIndex];
                if (next == rn){
                    break;
                }
            }
        }

        for ( i in ate){
            _heads.remove(i);
        }
    }

    public function isCircled( head:RingNode):Bool{
        var tmp = head._next[_nodeIndex];
        var isCir= true;
        while( tmp != head){
            if ( tmp == null){
                isCir= false;
                break;
            }
            tmp = tmp._next[_nodeIndex];
        }
        return isCir;
    }
}