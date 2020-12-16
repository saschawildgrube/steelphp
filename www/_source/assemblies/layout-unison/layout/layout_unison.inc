<?php

	require_once(GetWDKDir()."wdk_layout_bootstrap3.inc");

	class CMyLayout extends CLayoutBootstrap3
	{
		function CallbackInit()
		{
			$bResult = parent::CallbackInit();
			
			$this->GetWebsite()->AddHeader('<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />');

			// unison-clean.css is derived from unison.css without all embedded fonts
			$this->GetWebsite()->AddStyleSheet('unison','unison-clean');
			$this->GetWebsite()->AddStyleSheet('unison-fixes','unison-fixes');

			// Material Icons						
			$this->GetWebsite()->AddStyleSheetURL('font-materialicons','https://fonts.googleapis.com/icon?family=Material+Icons');
			$this->GetWebsite()->AddStyleSheet(		'font-materialicons-classes');

			// Font Awesome
			$this->GetWebsite()->AddStyleSheetURL('font-awesome','https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css');

			// Java Script files required by unison
			$this->GetWebsite()->AddJavaScript('page-preloading');
 			$this->GetWebsite()->AddJavaScript('modernizr','modernizr.custom');
 			$this->GetWebsite()->AddJavaScript('detectizr','detectizr.min');
			$this->GetWebsite()->AddJavaScript('jquery','jquery-2.1.4.min');
			$this->GetWebsite()->AddJavaScript('jquery.easing','jquery.easing.min');
			$this->GetWebsite()->AddJavaScript('bootstrap','bootstrap.min');
			$this->GetWebsite()->AddJavaScript('waves','waves.min');
			$this->GetWebsite()->AddJavaScript('smoothscroll');
			$this->GetWebsite()->AddJavaScript('waypoints','waypoints.min');
			$this->GetWebsite()->AddJavaScript('velocity','velocity.min');
			$this->GetWebsite()->AddJavaScript('isotope.pkgd','isotope.pkgd.min');
			$this->GetWebsite()->AddJavaScript('owl.carousel','owl.carousel.min');
			$this->GetWebsite()->AddJavaScript('magnific-popup','magnific-popup.min');
			$this->GetWebsite()->AddJavaScript('scrollreveal','scrollreveal.min');

			// This is called 'scripts' in the original unison distribution
			$this->GetWebsite()->AddJavaScript('unison');

			
			// WDK specific JavaScript files...
			$this->GetWebsite()->AddJavaScript('wdk');
			$this->GetWebsite()->AddJavaScript('wdk-progressindicator-activate');
			$this->GetWebsite()->AddJavaScript('wdk-progressindicatordownload-activate');
			
			// Load text ressources
			$this->GetWebsite()->LoadStringResources("layout-unison");
			
			return $bResult;
		}
	}
	
