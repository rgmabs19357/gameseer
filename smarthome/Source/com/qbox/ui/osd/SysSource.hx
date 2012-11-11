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

class SysSource extends OsdCommDlg{

    public function new ( dm:CommDialogMgr){
        super(dm);
        addChild( createElement());

#if neko
        TXT= "Source";
#else
        TXT= "信号源";
#end
    }
}