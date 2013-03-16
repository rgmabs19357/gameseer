package com.qbox.ui.osd;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.CommDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;
import com.qbox.logic.Screen;

import haxe.io.Bytes;
import haxe.io.BytesBuffer;

class ImgLightnessDlg extends ValueBarDlg{

    public function new ( dm:CommDialogMgr, s:Screen){
        super(dm, s);
        addChild( createElement());

        _value = 0;
        _max = 255;
#if neko
        TXT= "Blightness";
#else
        TXT= "亮度";
#end

    }

    override function dispatch(value:Int):Void{
        var bs:BytesBuffer  = new BytesBuffer();
        var shift:Int = _value<< 2;
        trace( shift);
        bs.addByte(shift >> 8);
        bs.addByte(shift);
        bs.addByte(shift >> 8);
        bs.addByte(shift);
        bs.addByte(shift >> 8);
        bs.addByte(shift);
        //bs.addByte(0x16);
        //bs.addByte(0x16);
        _screen.setOsd( Std.string(0x0a), Std.string(6), bs.getBytes(), cbFunc);
    }
    function cbFunc( a, s):Void{
    }
    
}
