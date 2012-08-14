package com.qbox.ui.osd;

import com.qbox.logic.QboxMgr;
import nme.events.MouseEvent;
import base.ui.InputDialog;
import base.ui.EmbedTextField;
import nme.text.TextFieldType;
import base.ui.ListDialogMgr;
import base.ui.ListDialog;
import base.ui.CommDialog;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import base.ui.CommDialogMgr;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;

class OptionMenuVerticalPos extends CommDialog{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

    }
    var _g:Sprite;
    var _c:Sprite;
    override function show(){
        if ( _g != null) {
            if ( _c != null){
                _g.removeChild(_c);
            }
            _c = new Sprite();
            _c.graphics.beginFill(0x888888);
            _c.graphics.drawRect( 300, 10,  300, 30);
            _c.addEventListener( MouseEvent.MOUSE_DOWN, onBarMouseDown); 
            _g.addChild(_c);
        }
        return super.show();
    }
    override function hide(){
        if ( _g != null && _c != null) {
            _c.removeEventListener(  MouseEvent.MOUSE_DOWN, onBarMouseDown ); 
            _g.removeChild(_c);
            _c = null;
        }
        return super.hide();
    }
    public function onBarMouseDown( evt:MouseEvent){
        if ( _c != null){
            _c.graphics.clear();
            _c.graphics.beginFill(0x00FF00);
            _c.graphics.drawRect( 300, 10, evt.localX - 300, 30 );
            _c.graphics.endFill();
            _c.graphics.beginFill(0x888888);
            _c.graphics.drawRect( evt.localX , 10, 600 - evt.localX , 30 );
            _c.graphics.endFill();
        }
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var option= new EmbedTextField();
        option.selectable = false;
#if neko
        option.text = "Menu Vertical Position";
#else
        option.text = "菜单垂直位置";
#end
        option.scaleX = 3;
        option.scaleY = 3;
        option.width = 100;
        option.height= 20;
        s.addChild( option);

        _g = new Sprite();
        s.addChild (_g);
        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}
