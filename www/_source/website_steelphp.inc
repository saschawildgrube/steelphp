<?php

	require_once("env.inc");
	require_once(GetWDKDir()."wdk_website_dynamic.inc");
	
	class CSteelPHPWebSite extends CDynamicWebSite
	{

		public $m_moduleSignin;
		public $m_moduleSignOut;
		public $m_moduleLogin;
		public $m_moduleUserEmail;


		function __construct(
			$arrayParams)
		{
			
			$arrayMeta = array();
			$arrayMeta["version"] = WDK_VERSION; 
			$arrayMeta["author"] = "Sascha Wildgrube";
			$arrayMeta["copyright"] = "?TID_COPYRIGHT?";
			$arrayMeta["copyright_since"] = WDK_COPYRIGHT_SINCE;
			
			
			$arrayConfig = array();
			
			$arrayConfig["session_mode"] = SESSION_MODE_SERVER_COOKIE;
			//$arrayConfig["session_mode"] = SESSION_MODE_SERVER_URL;       
			//$arrayConfig["session_mode"] = SESSION_MODE_SERVER_COMBINED;   

			$arrayConfig["session_ip"] = true;
			$arrayConfig["csrf_defuse"] = true;  
			
			$arrayConfig['opengraph'] = true;
			
	
			$arrayConfig["cache_deactivate"] = true;
			$arrayConfig["cache_allow_nocache"] = true;
			
			$arrayConfig["check_unresolvedtid"] = true;
			$arrayConfig["check_invalidtid"] = true;

			$arrayConfig["languages"][] = "EN"; 
			$arrayConfig["fallbacklanguage"] = "EN"; 
			
			$arrayConfig["countries"][] = "DEU";
			$arrayConfig["defaultcountry"] = "DEU";
			
			$arrayConfig["layouts"][] = "unison";
			
			$arrayConfig["protocols"][] = "https";
			
			$arrayConfig["admin_email"] = GetAdminEmail();
			
			$arrayConfig["defaultprivileges"] = array();
			
			$arrayConfig["privileges"][] = "USERADMIN";
			$arrayConfig["privileges"][] = "SYSTEMADMIN";
			
			/*
				This defines the rules for new passwords chosen by the user:
			*/
			$arrayConfig["passwordpolicy"] = array(
				"minimumlength" => 3,
				"requiredcharsnumeric" => true,
				"requiredcharsalpha" => false,
				"requiredcharsalphauppercase" => false,
				"requiredcharsalphalowercase" => false
				);
		
			/*
				This setting controls the support of seo friendly urls:
			*/
			$arrayConfig["seourl"] = "seourl";

		
			$arrayConfig["csvformat"] = "excel";
			
			parent::__construct(
				GetRootURL(),
				GetSourceDir(),
				GetDocumentRootDir(),
				$arrayMeta,
				$arrayConfig,
				$arrayParams,
				"website_steelphp");
					
		}
		
		function CallbackInitAssemblyLine(&$assemblyLine)
		{
			$assembly = new CAssembly($this,"layout-unison");
			$assemblyLine->AddAssembly($assembly);

			parent::CallbackInitAssemblyLine($assemblyLine);
		}
		
		function CallbackInitRoutingMap()
		{
			parent::CallbackInitRoutingMap();
			$this->LoadRoutingMap("default");
		}

		
		
		function CallbackInit()
		{
			$bResult = parent::CallbackInit();
			
			$this->AddHeader("<!--AVAILABILITY-CHECK-->");			

			$this->SetLayout("unison");
			
			$this->LoadStringResources("systemadmin");
			$this->LoadStringResources("wdkdocs");
			$this->LoadStringResources("steelphp");


			$passwordpolicy = new CPasswordPolicy();
			$passwordpolicy->SetPolicy($this->GetConfig("passwordpolicy"));

			$this->IncludeModule("user/login");
			$this->m_moduleLogin = new CLoginModule($this,"admin","logout");
			$this->RegisterModule($this->m_moduleLogin);
			
			$this->IncludeModule("user/useremail");
			$this->m_moduleUserEmail = new CUserEmailModule($this,true,true,"verifymail",60*60);
			$this->RegisterModule($this->m_moduleUserEmail);


			// LOGO
			$linkLogo = new CLinkElement($this,"logo");
			
			
			//$this->SetOutputItem("LOGO",$linkLogo->RenderLink($this->MakeContentURL('index'),'?TID_TITLE?'));
			
			$strSVG = '
<svg style="fill: #12185D; width: 120px; height: 30px;" version="1.1" id="steel-logo" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
	 viewBox="0 0 1066.2 273" xml:space="preserve">
<path class="steel-logo-path" d="M159.8,116c-28.3,15-49.8,30.1-65.7,46l-36.2,36.5c14.9-7.7,30.2-15.1,45.1-22.2c13.3-6.3,25.9-12.3,37.9-18.4
	c19.3-9.9,43.5-23.2,59.3-39l43.9-44.4c-14.1,7.9-29.6,15.2-44.8,22.2C186.1,102.9,172.5,109.2,159.8,116z M217.7,41.5
	c-28.3,15-49.8,30.1-65.7,46L115.8,124c14.9-7.7,30.2-15.1,45.1-22.2c13.3-6.3,25.9-12.3,37.9-18.4c19.3-9.9,43.5-23.2,59.3-39
	L302,0c-14.1,7.9-29.6,15.2-44.8,22.2C244,28.4,230.4,34.7,217.7,41.5z M101.9,190.5c-28.3,15-49.8,30.1-65.7,46L0,273
	c14.9-7.7,30.2-15.1,45.1-22.2c13.3-6.3,25.9-12.3,37.9-18.4c19.3-9.9,43.5-23.2,59.3-39l43.9-44.4c-14.1,7.9-29.6,15.2-44.8,22.2
	C128.2,177.4,114.6,183.7,101.9,190.5z M345.9,200.3c-9.8,0-18.7-2.8-26.6-8.5c-7.9-5.7-13.4-13.3-16.7-22.8l18.8-7
	c2.7,5.7,6.3,10.2,11,13.6c4.7,3.4,9.8,5.1,15.2,5.1c5.3,0,9.6-1.4,12.8-4.2c3.2-2.8,4.9-6.8,4.9-12c0-4.4-2.2-8.3-6.6-11.7
	c-4.4-3.4-10.5-6.9-18.4-10.3c-5-2.2-9-4.1-12-5.7c-3-1.6-6.4-3.9-10.2-6.8c-3.8-2.9-6.6-6.3-8.4-10.3c-1.9-3.9-2.8-8.3-2.8-13.2
	c0-9,3.4-16.7,10.3-22.8c6.9-6.2,15.9-9.3,27.2-9.3c8.9,0,16.7,2.4,23.4,7.3c6.7,4.9,11.1,11.1,13.3,18.6l-18.6,6.3
	c-4.2-8.5-10.6-12.7-19.3-12.7c-4.5,0-8.2,1.2-11.1,3.5c-2.9,2.3-4.3,5.5-4.3,9.6c0,0.9,0.1,1.8,0.3,2.7c0.2,0.9,0.6,1.7,1.2,2.4
	c0.6,0.8,1.1,1.4,1.6,2.1c0.5,0.6,1.3,1.3,2.4,2.1c1.1,0.8,2,1.4,2.8,1.8c0.8,0.5,1.9,1.1,3.4,1.8c1.5,0.8,2.7,1.3,3.5,1.7
	c0.8,0.3,2.1,1,4,1.8c1.9,0.9,3.2,1.5,4,1.8c4.9,2.2,8.9,4.3,12.2,6.2c3.2,1.9,6.8,4.4,10.8,7.6c3.9,3.1,6.9,6.8,9,11.1
	c2.1,4.3,3.1,9,3.1,14.1c0,11.1-3.9,19.9-11.7,26.4C366.7,197,357.2,200.3,345.9,200.3z M444.2,200.3c-17.4,0-26-8-26-24.2v-49.2
	h-18.6v-17.5h18.6V82.3l20-9.6v36.7h30.2v17.5h-30.2v45.4c0,6.8,4.2,10.3,12.5,10.3c4.9,0,10-1.4,15.3-4.2l-2.4,17.9
	C458.4,198.9,451.9,200.3,444.2,200.3z M570.4,149.4c0-13.8-3.6-24.2-10.8-31.4c-7.2-7.1-16.4-10.7-27.8-10.7
	c-13,0-23.3,4.1-30.9,12.4c-7.6,8.3-11.5,19.6-11.5,34c0,14.1,3.8,25.4,11.4,33.9c7.6,8.5,17.9,12.7,31,12.7
	c12.8,0,23.4-4.6,31.8-13.7l-12-12.7c-5.3,5.8-11.9,8.7-19.6,8.7c-6.1,0-11.1-1.9-15-5.6c-3.9-3.8-6.5-8.9-7.7-15.4h60.4
	C570.1,158.5,570.4,154.5,570.4,149.4z M509.1,144.5c1-6.1,3.5-10.9,7.4-14.4c3.9-3.5,9-5.2,15.4-5.2c5,0,9.2,1.7,12.8,5
	c3.5,3.3,5.6,8.2,6.2,14.7H509.1z M671,149.4c0-13.8-3.6-24.2-10.8-31.4c-7.2-7.1-16.4-10.7-27.8-10.7c-13,0-23.3,4.1-30.9,12.4
	c-7.6,8.3-11.5,19.6-11.5,34c0,14.1,3.8,25.4,11.4,33.9c7.6,8.5,17.9,12.7,31,12.7c12.8,0,23.4-4.6,31.8-13.7l-12-12.7
	c-5.3,5.8-11.9,8.7-19.6,8.7c-6.1,0-11.1-1.9-15-5.6c-3.9-3.8-6.5-8.9-7.7-15.4h60.4C670.8,158.5,671,154.5,671,149.4z M609.7,144.5
	c1-6.1,3.5-10.9,7.4-14.4c3.9-3.5,9-5.2,15.4-5.2c5,0,9.2,1.7,12.8,5c3.5,3.3,5.6,8.2,6.2,14.7H609.7z M855,87.5
	c-6.5-7.3-16.8-10.9-30.8-10.9h-42.9v121.6h20.7V152h22.2c13.4,0,23.6-3.8,30.4-11.4c6.8-7.6,10.2-16.4,10.2-26.3
	C864.8,103.7,861.5,94.8,855,87.5z M839.2,127.1c-3.1,3.6-7.7,5.4-14,5.4h-23.3V96h23.3c6.5,0,11.2,1.9,14.2,5.6
	c3,3.7,4.4,7.9,4.4,12.7C843.8,119.2,842.2,123.5,839.2,127.1z M1056.4,87.5c-6.5-7.3-16.8-10.9-30.8-10.9h-42.9v121.6h20.7V152
	h22.2c13.4,0,23.6-3.8,30.4-11.4c6.8-7.6,10.2-16.4,10.2-26.3C1066.2,103.7,1063,94.8,1056.4,87.5z M1040.6,127.1
	c-3.1,3.6-7.7,5.4-14,5.4h-23.3V96h23.3c6.5,0,11.2,1.9,14.2,5.6c3,3.7,4.4,7.9,4.4,12.7C1045.2,119.2,1043.7,123.5,1040.6,127.1z
	 M960.9,76.6v121.6h-20.6c0,0,0,0,0-0.1v-52.9H901v53h-20.6c0,0,0,0,0-0.1V86.4l20.7-9.9h0v49.2h39.2V86.4L960.9,76.6z M688.7,117.4
	V95.3l46.4-22.2l0,107.6h25.9v17.5h-71.7v-17.5h25.9l0-75.9L688.7,117.4z"/>
</svg>
';
			
			$this->SetOutputItem("LOGO",
				$linkLogo->RenderLink($this->MakeContentURL('index'),$strSVG)
				);
			
			

			// CTA
			if ($this->GetContent() != "gettingstarted")
			{
				$linkCTA = new CLinkElement($this,"calltoaction");
				$this->SetOutputItem("CTA",$linkCTA->RenderLink($this->MakeContentURL("gettingstarted"),'?TID_LINK_CTA?'));
			}

			
			if ($this->GetLayout() == 'unison')
			{
				if (FindString($this->GetContent(),'wdkdocs') == 0)
				{
					$this->SetFramework('sidebar');	
				}
				if ($this->GetContent() == 'index')
				{
					
				}
			}
			
			// Converting WDK into SteelPHP
			$this->SetOutputItem("WDK","SteelPHP");
			$this->SetOutputItem("WDK_DOCS_URL",$this->MakeContentURL("wdkdocs"));
			$this->SetOutputItem("WDK_SCAFFOLDER_URL",$this->MakeContentURL("scaffolder"));

			// FORK ME ON GITHUB
			$this->IncludeElement('forkmeongithub');
			$forkmeongithub = new CForkMeOnGithubElement($this,'default');
			$this->SetOutputItem('FORKMEONGITHUB',$forkmeongithub->RenderForkMeOnGithub('saschawildgrube','steelphp'));

			

			return $bResult;
		}
		
		function GetSiteName()
		{
			return "SteelPHP";
		}
		
		function GetSiteTeamEmail()
		{
			return "info@".GetMailDomain();
		}

		function GetSiteTeamName()
		{
			return "The Steel Team";
		}
	
	
		function CallbackUserCheckName($strUsername)
		{
			if (parent::CallbackUserCheckName($strUsername) == false)
			{
				return false;	
			}
			if (StringCheckCharSet($strUsername,CHARSET_ALPHANUMERIC_LOWERCASE) == false)
			{
				return false;	
			}
			return true;
		}
		
		function CallbackUserChangePassword($strOldPassword,$strNewPassword)
		{
			$bResult = parent::CallbackUserChangePassword($strOldPassword,$strNewPassword);
			if (!$bResult)
			{
				return false;
			}
			
			$strUserID = $this->GetAuthUserID();
			if ($strUserID == "")
			{
				return false;	
			}

			return true;
		}

	
	
		function CallbackPreContent()
		{
			/*
				Called before the actual content rendering takes place.
			*/
		}

		function CallbackPostContent()
		{
			/*
				Called after the actual content rendering takes place.
			*/			
			
			// DATETIME
			$this->IncludeElement("datetime");
			$datetime = new CDateTimeElement($this,"default");
			$this->SetOutputItem("DATETIME",$datetime->RenderDateTime(GetTimeNow()));	

			// USER STATUS
			//$this->SetOutputItem("USERSTATUS",$this->m_moduleLogin->RenderModule("status"));

			// LANGUAGE SELECTION
			/*
			$this->IncludeModule("user/languageselection");
			$languageselectionModule = new CLanguageSelectionModule($this,"index");
			$this->SetOutputItem("LANGUAGESELECTION",$languageselectionModule->RenderModule("toolbar"));	
			*/
		}
		
		function CallbackRenderSpecialContent($strContentID)
		{
			/*
				Before trying to load the content from a file, this function is called.
				If the function returns "", the content is loaded from a file.
				If the function returns anything else, the returned string is used as the content.
			*/
			
			/*
				The following is required for the signin process.
				A user has entered a user name, password, and mail address.
				Then a mail has been sent to the user with a confirmation link.
				This link includes the "signin" parameter which is handled here.
				The actual logic takes place in the user/signin module.
			*/
			if ($this->GetVar("signin") != "")
			{
				$strOutput = $this->m_moduleSignin->RenderModule("default");
				$strOutput .= $this->m_moduleLogin->RenderModule("form");
				return $strOutput;
			}		
			
			/*
				The following code manages a user's request to change the
				stored email address.
				After the user has changed the email address in the user
				settings page in the module user/useremail a mail has been
				sent to the user asking for confirmation.
				This mail contains a confirmation link that includes the
				"verifymail" parameter.
				The actual logic is in the module user/useremail.
			*/			
			if ($this->GetVar("verifymail") != "")
			{
				$strOutput = $this->m_moduleUserEmail->RenderModule("verification");
				return $strOutput;
			}			
			
			
			return parent::CallbackRenderSpecialContent($strContentID); 
		}

		function CallbackRenderContentException()
		{
			/*
				This function is called if a requested content is not found.
				If you were implementing a wiki, this would be the place to create a
				new page.
			*/
			return parent::CallbackRenderContentException();
		}


		function CallbackRenderGenericOutputItem($strItem, $arrayAttributes)
		{
			switch ($strItem)
			{
			default:
				return parent::CallbackRenderGenericOutputItem($strItem, $arrayAttributes);
			}
		}
		

		function CallbackRenderNavigation($strOutput)
		{
			/*
				This function is called after content rendering is complete.
				This implementation replaces different tags from the framework layout
				with corresponding navigation elements.
			*/
			
			$navigationtree = new CNavigationTree();
			$navigationtree->LoadNavigationTree($this,"");
			$navigationtree->SetCurrentContext($this->GetContent());
			$navigationtree->SetContextParameterName("content");

			if (FindString($strOutput,"{NAVIGATION_HORIZONTALPATH}") != -1)
			{
				$navigation = new CNavigationElement($this,"horizontalpath");
				$this->SetOutputItem("NAVIGATION_HORIZONTALPATH",$navigation->RenderNavigationHorizontalPath($navigationtree));
	    }
         
			if (FindString($strOutput, "{NAVIGATION_VERTICALPATH}") != -1)
			{
				if (FindString($this->GetContent(),"wdkdocs") == 0)
				{
					$navigationtreeVertical = new CNavigationTree();
					$navigationtreeVertical->LoadNavigationTree($this,"wdkdocs");
					$navigationtreeVertical->SetCurrentContext($this->GetContent());
					$navigationtreeVertical->SetContextParameterName("content");					 
				}
				else
				{
					$navigationtreeVertical = $navigationtree;
				}
				$navigation = new CNavigationElement($this,"verticalpath");
				$this->SetOutputItem("NAVIGATION_VERTICALPATH",
					$navigation->RenderNavigationVerticalPath($navigationtreeVertical,0));
      }
         
			if (FindString($strOutput, "{NAVIGATION_CURRENTPATH}") != -1)
			{ 
				$navigation = new CNavigationElement($this,"currentpath");
				$this->SetOutputItem("NAVIGATION_CURRENTPATH",
					$navigation->RenderNavigationCurrentPath($navigationtree));
			}
			
			if (FindString($strOutput, "{NAVIGATION_VERTICALCURRENTPATH}") != -1)
			{ 
				$navigation = new CNavigationElement($this,"verticalcurrentpath");
				$this->SetOutputItem("NAVIGATION_VERTICALCURRENTPATH",
					$navigation->RenderNavigationVerticalCurrentPath($navigationtree));
			}
         
			if (FindString($strOutput, "{NAVIGATION_FOOTER}") != -1)
			{
				$navigationtree_footer = new CNavigationTree();
				$navigationtree_footer->LoadNavigationTree(
					$this,
					"footer");
				$navigationtree_footer->SetCurrentContext($this->GetContent());
				$navigationtree_footer->SetContextParameterName("content");
         		
				$navigation = new CNavigationElement($this,"footer");
				$this->SetOutputItem("NAVIGATION_FOOTER",$navigation->RenderNavigationHorizontalPath($navigationtree_footer));
			}
		}




		function CallbackCheckCondition($strCondition)
		{
			if ($strCondition == "wdkdocs")
			{
				return true;	
			}
			if ($strCondition == "wdkdocs-wip")
			{
				return false;	
			}
			if ($strCondition == "useradmin")
			{
				if ($this->CheckCondition("systemadmin") == true)
				{
					return true;
				}
			}

			if ($strCondition == "admin")
			{
				if ($this->CheckCondition("useradmin") == true)
				{
					return true;
				}
				if ($this->CheckCondition("systemadmin") == true)
				{
					return true;
				}
			}			
			
			return parent::CallbackCheckCondition($strCondition);	
		}
		
		
		
		
		function CallbackGetDateLocalFormat($strCountryID)
		{
			switch ($strCountryID)
			{
			default:
				return "%Y-%m-%d";
			}
		}

		function CallbackGetTimeLocalFormat($strCountryID)
		{
			switch ($strCountryID)
			{
				default:
					return "%H:%M:%S";

			}
		}
		
		

	}
	

