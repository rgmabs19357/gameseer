package com.pictionary.ui;

import base.ui.EmbedTextField;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.eclecticdesignstudio.dialog.DialogManager;
import com.eclecticdesignstudio.dialog.Dialog;
import com.eclecticdesignstudio.dialog.DialogType;
import com.eclecticdesignstudio.dialog.DialogData;
import com.eclecticdesignstudio.dialog.events.DialogEvent;

import nme.events.MouseEvent;
import nme.events.Event;
import nme.display.DisplayObject;
import base.ui.ListDialogMgr;
import base.ui.SubListDialogMgr;
import base.ui.InputDialog;
import com.pictionary.ui.ConnDrawingDlg;

import haxe.Timer;

class MainStage extends ListDialogMgr {


    var _exit:Sprite;

#if (cpp || neko)
    public function initExit():Void{
        _exit = new Sprite();
        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("exit"));
        _exit.addChild( bm);
        _exit.x = 50;
        _exit.y= nme.Lib.current.stage.stageHeight - 100;
        _exit.addEventListener( MouseEvent.CLICK, onExit);
    }

    public function onExit( evt:MouseEvent):Void{
        nme.system.System.exit();
    }

    function new(){ 
        super(nme.Lib.current);
        initExit();
    }
#elseif flash
    function new(){ 
        super(nme.Lib.current);
    }
#end


    public function createDlgs(){
        var name:String = DataLoader.getInst().getData("usrname");
        if (name == null) {
            name = "玩家";
        }
        new base.ui.SocialBinderDlg(this);
        //new UserNameInputDlg( this, name, 0, "输入名称:");
        //new ConnDrawingDlg( this);
#if !flash
        //new HostDialog( this  );
#end
        new DrawingDlg( this, "SNS猜猜",0 );
        new SubjectsDlg( this);
    }


    public override function showListDialog( ):Void{
        if (_exit!= null &&  _exit.parent == null  ) { nme.Lib.current.addChild(_exit); }
        super.showListDialog();
    }

    public override function hideListDialog( ):Void{
        if (_exit!= null &&  _exit.parent != null  ) { nme.Lib.current.removeChild(_exit); }
        super.hideListDialog();
    }

    override function clear(){
        hideListDialog();
        //trace("clear1");
        super.clear();
        //trace("clear2");
    }

    public function resetDlgs(){
        getInst().removeAll();
        getInst().createDlgs();
    }

    public override function createElement(name:String, id:Int):Sprite{
        var txt:EmbedTextField = new EmbedTextField();
        txt.text = name;
        txt.scaleX = 3;
        txt.scaleY = 3;
        txt.x = 220;
        txt.width = nme.Lib.current.stage.stageWidth/txt.scaleX - 220/txt.scaleX;
        txt.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;
        txt.setBorder(true);
        txt.selectable = false;

        var txt1:EmbedTextField = new EmbedTextField();
        txt1.text = Std.string(id);
        txt1.scaleX = 1;
        txt1.scaleY = 3;
        txt1.setBorder(true);
        txt1.width = 100;
        txt1.x = 120;
        txt1.height = nme.Lib.current.stage.stageHeight/10/txt1.scaleY;
        txt1.selectable = false;

        var bm:Bitmap = new Bitmap( DataLoader.getInst().bms_.get("trunk") );
        //bm.height = nme.Lib.current.stage.stageHeight/10/txt.scaleY;

        var s:Sprite = new Sprite();
        s.addChild( bm);
        s.addChild( txt1);
        s.addChild( txt);
        //var w:Float = nme.Lib.current.stage.stageWidth / txt.width;
        //s.width=  nme.Lib.current.stage.stageWidth;
        s.height = nme.Lib.current.stage.stageHeight/10;
        //txt.scaleY = 2;
        return s;
    }

    static var inst:MainStage;
    inline public static function getInst():MainStage{
        if ( inst == null) {
            inst = new MainStage();
        }
        return inst;
    }


}

