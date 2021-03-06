<?php

	class CMyScaffolder extends CScaffolder
	{
		
		function OnPrepareForm(CFormDefinition &$formDef)
		{

			$formDef->AddControlText(
 				"ROOTURL",
 				$this->GetVarName("rooturl"),
 				$this->GetTID("CONTROL_ROOTURL"),
 				$this->GetVar("rooturl"),
		   	50,
 				50);

			$formDef->AddControlText( 
 				"SITEDIR",
 				$this->GetVarName("sitedir"),
 				$this->GetTID("CONTROL_SITEDIR"),
 				$this->GetVar("sitedir"),
		   	50,
 				100);	

			$formDef->AddControlText(
 				"WEBSITENAME",
 				$this->GetVarName("websitename"),
 				$this->GetTID("CONTROL_WEBSITENAME"),
 				$this->GetVar("websitename"),
		   	30,
 				30);

			$formDef->AddControlText(
 				"WEBSITENAMEVERBOSE",
 				$this->GetVarName("websitenameverbose"),
 				$this->GetTID("CONTROL_WEBSITENAMEVERBOSE"),
 				$this->GetVar("websitenameverbose"),
		   	50,
 				50);
 				
			$formDef->AddControlCheckbox( 
 				"SEOURL",
 				$this->GetVarName("seourl"),
 				$this->GetTID("CONTROL_SEOURL"),
 				$this->GetVar("seourl"));	
		 				 
 				
			$formDef->AddControlText(
 				"TMPDIR",
 				$this->GetVarName("tmpdir"),
 				$this->GetTID("CONTROL_TMPDIR"),
 				$this->GetVar("tmpdir"),
		   	50,
 				100);		 				
			
			$formDef->AddControlText(
 				"ADMINEMAIL",
 				$this->GetVarName("adminemail"),
 				$this->GetTID("CONTROL_ADMINEMAIL"),
 				$this->GetVar("adminemail"),
		   	50,
 				100);		

 			$formDef->AddControlText(
 				"SITETEAM",
 				$this->GetVarName("siteteam"),
 				$this->GetTID("CONTROL_SITETEAM"),
 				$this->GetVar("siteteam"),
		   	50,
 				50);
 				
 			$formDef->AddControlText(
 				"PUBLISHER",
 				$this->GetVarName("publisher"),
 				$this->GetTID("CONTROL_PUBLISHER"),
 				$this->GetVar("publisher"),
		   	50,
 				50);

 			$formDef->AddControlText(
 				"AUTHOR",
 				$this->GetVarName("author"),
 				$this->GetTID("CONTROL_AUTHOR"),
 				$this->GetVar("author"),
		   	50,
 				50);

 			$formDef->AddControlText(
 				"METAKEYWORDS",
 				$this->GetVarName("metakeywords"),
 				$this->GetTID("CONTROL_METAKEYWORDS"),
 				$this->GetVar("metakeywords"),
		   	50,
 				200);

 			$formDef->AddControlTextArea(
 				"METADESCRIPTION",
 				$this->GetVarName("metadescription"),
 				$this->GetTID("CONTROL_METADESCRIPTION"),
 				$this->GetVar("metadescription"),
		   	50,
 				6);

		}
		
		function OnGetParams(&$arrayParams)
		{
			$arrayParams["rooturl"] = $this->GetVar("rooturl");

			$arrayParams["WebSiteName"] = $this->GetVar("websitename");
			$arrayParams["websitename"] = StringLowerCase($arrayParams["WebSiteName"]);
			$arrayParams["WEBSITENAME"] = StringUpperCase($arrayParams["WebSiteName"]);
			
			$arrayParams["WebSiteNameVerbose"] = $this->GetVar("websitenameverbose");
			
			$arrayParams["WebSiteNameShort"] = $this->GetVar("websitenameshort");
		
			$arrayParams["sitedir"] = $this->GetVar("sitedir");
			if ($arrayParams["sitedir"] == "/")
			{
				$arrayParams["sitedir"] = "";
			}
			if (StringLength($arrayParams["sitedir"]) > 0)
			{
				if (StringSection($arrayParams["sitedir"],0,1) == "/")
				{
					$arrayParams["sitedir"] = StringSection($arrayParams["sitedir"],1);
				}	
				if (StringSection($arrayParams["sitedir"],-1,1) != "/")
				{
					$arrayParams["sitedir"].="/";
				}
			}
			
			$arrayParams["sitedir_ls"] = "/".$arrayParams["sitedir"]; // "ls" is for "leading slash"
			
			$arrayParams["tmpdir"] = $this->GetVar("tmpdir");
			
			$arrayParams["adminemail"] = $this->GetVar("adminemail");
			
			$arrayParams["siteteam"] = $this->GetVar("siteteam");			
			
			$arrayParams["publisher"] = $this->GetVar("publisher");
			if ($arrayParams["publisher"] == "")
			{
				$arrayParams["publisher"] = $arrayParams["siteteam"];
			}
			
			$arrayParams["author"] = $this->GetVar("author");
			if ($arrayParams["author"] == "")
			{
				$arrayParams["author"] = $arrayParams["publisher"];
			}
						
			$arrayParams["copyrightsince"] = StringSection(RenderDateNow(),0,4);
			
			$arrayParams["metakeywords"] = $this->GetVar("metakeywords");
			$arrayParams["metadescription"] = $this->GetVar("metadescription");
			
			if ($this->GetVar("seourl") == false)
			{
				$arrayParams["seourlcommenttag"] = "#";
				$arrayParams["seourlparam"] = "";
			}
			else
			{
				$arrayParams["seourlcommenttag"] = "";
				$arrayParams["seourlparam"] = "seourl";
			}
			
		}
		
		function OnCheckParams($arrayParams,&$arrayErrors)
		{
			$strRootURL = $arrayParams["rooturl"];
			if (StringSection($strRootURL,0,4) == "http")
			{
				$arrayErrors["ROOTURL"]	= $this->GetTID("ERROR_ROOTURL_INVALID");
			}
			else
			{
				$strRootURL = "http://".$strRootURL;
				if (IsValidURL($strRootURL) != true)
				{
					$arrayErrors["ROOTURL"]	= $this->GetTID("ERROR_ROOTURL_INVALID");
				}
			}
			
			$strSiteDir = $arrayParams["sitedir"];
			if (IsValidPath("a/".$strSiteDir) != true)
			{
				$arrayErrors["SITEDIR"]	= $this->GetTID("ERROR_SITEDIR_INVALID");
			}
			
			$strWebsiteName = $arrayParams["WebSiteName"];
			if ((StringCheckCamelCase($strWebsiteName) == false) || ($strWebsiteName == ""))
			{
				$arrayErrors["WEBSITENAME"]	= $this->GetTID("ERROR_WEBSITENAME_INVALID");
			}

			$strWebsiteNameVerbose = $arrayParams["WebSiteNameVerbose"];
			if ( $strWebsiteNameVerbose == "")
			{
				$arrayErrors["WEBSITENAMEVERBOSE"]	= $this->GetTID("ERROR_WEBSITENAMEVERBOSE_INVALID");
			}

		
			if ( IsValidEmail($arrayParams["adminemail"]) == false)
			{
				$arrayErrors["ADMINEMAIL"]	= $this->GetTID("ERROR_EMAIL_INVALID");
			}
			
			if ($arrayParams["author"] == "")
			{
				$arrayErrors["AUTHOR"]	= $this->GetTID("ERROR_AUTHOR_INVALID");
			}
			if ($arrayParams["siteteam"] == "")
			{
				$arrayErrors["SITETEAM"]	= $this->GetTID("ERROR_SITETEAM_INVALID");
			}

			

		}
		
		function OnAddAdditionalArchiveFiles($arrayParams,&$arrayArchiveFiles)
		{
			$arrayFiles = ReadDirectory(GetWDKDir(),true);
			foreach ($arrayFiles as $strFilePath)
			{
				if (StringSection($strFilePath,-1,1) != "/")	
				{
					$arrayArchiveFiles[] = array
						(
						"archivefilepath" => "www/".$arrayParams["sitedir"]."_source/wdk/".$strFilePath,
						"filepath" => GetWDKDir() . $strFilePath
						);	
				}
			}
		}


	}
	
