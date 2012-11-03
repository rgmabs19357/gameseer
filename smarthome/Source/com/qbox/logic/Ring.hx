package com.qbox.logic;

import haxe.io.Bytes;


class Ring{

    public var _heads:Array<RingNode>;
    public var _nodeIndex:Int;
    public var _isRingSetup:Bool;
    public var _count:Int;
    public var _cb:Dynamic->Void;


    //only support ring out port 1 or ring out port 2 currently
    public function new( index:Int){
        _heads = new Array<RingNode>();
        _nodeIndex = index;
        _isRingSetup = false;
        _count = 0;
    }


    public function isAvailable():Bool{
        for ( i in _heads){
        }

        return true;
    }

    public function setupRing( wnd:Wnd, cb:Dynamic->Void){
        if ( _count > 0) {trace("_count:"+_count);return ;}

        for ( i in _heads){
            var n = i;
            while (n !=null ){
#if !neko
                if(n._screen.isConected() == false){
                    trace("there is a qbox not yet connected: "+ n._screen._ipv4);
                    return;
                }
#end
                n._screen.setRingChannel( n._outport[_nodeIndex], n._inport[_nodeIndex], cbSetupRing, wnd);
                ++_count;
                n = n._next[_nodeIndex];
                if ( n == i){
                    break;
                }
            }

        }
        _isRingSetup = true;
        _cb = cb;
    }

    function cbSetupRing( args:Dynamic, s:Screen){
        if ( args.get("error") == "1") {
            trace("there is a error occurred at qbox: "+ s._ipv4);
            _cb("error");
            return;
        }
        --_count;
        if (_count == 0){
            _cb("");
            _cb = null;
        }
    }

    public function setup753( wnd:Wnd, ss:Array<Screen>, c:Channel,  cb:Dynamic->Void):Bool{
        if ( _count > 0) {trace("_count:"+_count);return false ;}

        for ( i in ss){
            if ( isInRing(i) == false )  {
                trace("not in ring!");
                return false;
            }
            if ( i.has753Available() ){
                trace("not 753 available!");
            }
        }

        for (i in ss){
            ++_count;
            if ( i == c._screen){
                i.set753Channel( c._inport, cbSetupRing, wnd);
            }else{
                i.set753Channel( i._ringNode._inport[_nodeIndex] , cbSetupRing, wnd);
            }
        }
        return true;
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
                //trace(n._col);
                //trace(n._row);
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