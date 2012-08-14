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
import base.ui.CommDialog;

import com.qbox.logic.Qbox;
import com.qbox.logic.Channel;

class OsdSysDlg extends ListDialog{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new SysModel(_listDialogMgr);
        i =new SysMachinePosNum(_listDialogMgr);
        i =new SysSource(_listDialogMgr);
        i =new SysImgResolution(_listDialogMgr);
        i =new SysRunningTime(_listDialogMgr);
        i =new SysSoftwareVersion(_listDialogMgr);
        i =new SysLEDLightTemperature(_listDialogMgr);
    }

    public function createElement():Sprite{
        var s:Sprite = new Sprite();

        var sys= new EmbedTextField();
        sys.selectable = false;
#if neko
        sys.text = "System Setting";
#else
        sys.text = "系统设定";
#end
        sys.scaleX = 3;
        sys.scaleY = 3;
        sys.width = 50;
        sys.height= 20;
        s.addChild( sys);

        s.height = nme.Lib.current.stage.stageHeight/15;
        return s;
    }
}