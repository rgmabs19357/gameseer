package com.qbox.logic;

import base.data.DataLoader;


class ChannelMgr {

    public static var inst:ChannelMgr;
    inline public static function getInst():ChannelMgr{
        if ( inst == null) {
            inst = new ChannelMgr();
        }
        return inst;
    }



    //Array< Qbox>, container of Qboxes.
    public var _channels:Array<Channel>;


    public function new(){
        _channels =  new Array<Channel>();
    }

    public function createChannel():Channel{
        var c = new Channel( ""+_channels.length );
        _channels.push( c);
        return c;
    }

    public function removeQbox( c:Channel){
        for ( i in _channels){
            if ( c == i ){
                _channels.remove( i ) ;
                break;
            }
        }
    }
}
