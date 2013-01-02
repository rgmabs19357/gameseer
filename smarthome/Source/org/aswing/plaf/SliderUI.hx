/*
 Copyright aswing.org, see the LICENCE.txt.
*/

package org.aswing.plaf;


import org.aswing.Insets;

/**
 * Pluginable ui for Slider.
 * @see org.aswing.JSlider
 * @author paling
 */
interface SliderUI implements ComponentUI{
	
	function getTrackMargin():Insets;
	
}