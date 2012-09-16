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

class ImgDlpSettingDlg extends OsdListDlg{

    public function new ( dm:ListDialogMgr){
        super(dm);
        addChild( createElement());

        var i:CommDialog =new DlpSettingRedLightness(_listDialogMgr);
        i =new DlpSettingGreenLightness(_listDialogMgr);
        i =new DlpSettingBlueLightness(_listDialogMgr);
        i =new DlpSettingRedContrast(_listDialogMgr);
        i =new DlpSettingGreenContrast(_listDialogMgr);
        i =new DlpSettingBlueContrast(_listDialogMgr);
#if neko
        TXT= "DLP setting";
#else
        TXT= "DLP设定";
#end
    }

}
