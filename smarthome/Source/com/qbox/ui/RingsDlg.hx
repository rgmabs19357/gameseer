package com.qbox.ui;

import com.qbox.logic.QboxMgr;
import base.ui.FixedDlg;
import base.ui.ListFixedDlg;
import base.ui.CommDialogMgr;
import base.ui.ListDialogMgr;
import nme.display.Sprite;
import nme.display.Bitmap;
import base.data.DataLoader;
import com.qbox.logic.ScreenMgr;
import com.qbox.logic.Wnd;
import com.qbox.ui.PlusRight;
import com.qbox.ui.PlusDown;


class RingsDlg extends ListFixedDlg{
    public function new ( dm:CommDialogMgr ){
        super(dm, new Bitmap( DataLoader.getInst().bms_.get("ring")));

        x = 90;
        y= nme.Lib.current.stage.stageHeight - 80;

        new PlusDown(_listDialogMgr);
        new PlusRight(_listDialogMgr);
    }

    public override function onMouseClick( ):Void{
        if ( QboxMgr.getInst()._qboxes.length <2) {
            trace("have to define more than one qbox for RING!");
            return;
        }
        if ( _mgr.isAnimating() == false){
            _listDialogMgr.removeAllMovables();
        }
        super.onMouseClick();
    }
}