package com.blueseer.ui;

import base.ui.Native;
import com.blueseer.cmd.CommandMgr;
import com.blueseer.device.DeviceMgr;
import com.blueseer.ui.UIMgr;
import base.ui.EmbedTextField;
import nme.display.Bitmap;
import base.data.DataLoader;
import nme.events.Event;
import nme.events.MouseEvent;
import nme.display.Sprite;
import nme.text.TextFieldType;

import base.ui.CommDialog;
import base.ui.ListDialogMgr;

class CommandCreatorDialog extends CommDialog{
    var _usrInput:EmbedTextField ;
    var _hint:EmbedTextField ;
    var _OK:EmbedTextField ;
    var _Cancel:EmbedTextField ;

    public function new ( mgr:ListDialogMgr ){
        var str:String = "创建指令";
        var id:Int = 0;
        _uniqueId = str+id;
        var s:Sprite = mgr.createElement( str, id);
        super( mgr);
        addChild(s);
    }

    public function onLoop(evt:Event){
        var res:String = Native.inputData();
        if ( res != null ){
            nme.Lib.current.removeEventListener( Event.ENTER_FRAME, onLoop);
            if ( res.length > 0 && res.substr(0, 1) != "_" ) {
                createCmd( res);
            }
        }
    }

    override function onMouseClick(){
        if ( cast(_mgr,ListDialogMgr).isAnimating()) return;
#if sys
        Native.nativeInput();
        nme.Lib.current.addEventListener( Event.ENTER_FRAME, onLoop);
#else
        flashInput();
        cast(_mgr,ListDialogMgr).hideListDialog();
#end
    }


#if flash
    public function flashInput():Void{

        if ( _usrInput == null ){
            _usrInput= new EmbedTextField();
            _hint= new EmbedTextField();
            _OK= new EmbedTextField();
            _Cancel= new EmbedTextField();
            _OK.text = "OK";
            _OK.scaleX = 3;
            _OK.scaleY = 3;
            _OK.y = 180;
            _OK.x = 100;
            _OK.height = 20;
            _OK.width = 20;
            _OK.setBorder(true);
            _OK.selectable = false;
            _Cancel.text = "Cancel";
            _Cancel.scaleX = 3;
            _Cancel.scaleY = 3;
            _Cancel.y = 180;
            _Cancel.x = 200;
            _Cancel.setBorder(true);
            _Cancel.height = 20;
            _Cancel.width = 20;
            _Cancel.selectable = false;
            _OK.setBorder(true);
            _hint.selectable = false;
            _hint.text = "输入你要创建的指令名称";
            _hint.scaleX = 3;
            _hint.scaleY = 3;
            _hint.width = nme.Lib.current.stage.stageWidth;
            _hint.height= 20;
            _usrInput.text = "";
            _usrInput.type = INPUT;
            _usrInput.scaleX = 3;
            _usrInput.scaleY = 3;
            _usrInput.width = nme.Lib.current.stage.stageWidth;
            _usrInput.height= 20;
            _usrInput.setBorder(true);
            _usrInput.y= 100;
            _OK.addEventListener( MouseEvent.CLICK, onOK);
            _Cancel.addEventListener( MouseEvent.CLICK, onCancel);
            _elements.push(  _OK);
            _elements.push(_Cancel);
            _elements.push(_hint);
            _elements.push(_usrInput);
        }
        showElements();
        nme.Lib.current.stage.focus = _usrInput;
    }
#end

    public function swichBackToCMDView():Void{
        hideElements();
        cast(_mgr,ListDialogMgr).showListDialog( );
    }
    public function createCmd( name:String):Void{
        CommandMgr.getInst().createCmd(name);
    }

    public function onOK(evt:MouseEvent){
        var cmdName:String = _usrInput.text;
        if (cmdName != null &&  cmdName.length > 0){
            //trace("cmd: "+ _usrInput.text);
            createCmd(cmdName);
        }else swichBackToCMDView();
    }

    public function onCancel(evt:MouseEvent){
        swichBackToCMDView();
    }
}
