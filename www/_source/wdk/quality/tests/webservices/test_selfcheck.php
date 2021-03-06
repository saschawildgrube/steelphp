<?php
	
	require_once(GetSourceDir()."webservices_directory.inc");
	
	class CTest extends CUnitTest
	{
		function __construct()
		{
			$arrayConfig = array();
			$arrayConfig["webservices"] = GetWebServicesDirectory();			
			parent::__construct("Test web services",$arrayConfig);
		}
	
		function OnInit()
		{
			$this->SetVerbose(true);
			$this->SetResult(true);
			return parent::OnInit();	
		}
	
		function OnTest()
		{
			parent::OnTest();	
	
			$arrayWebservices = $this->GetConfig("webservices");
			$this->Trace($arrayWebservices);
			foreach ($arrayWebservices as $strWebservice => $arrayWebservice)
			{
				$arrayParams = array();
				$arrayParams["command"] = "selfcheck";
				$consumer = new CWebServiceConsumerWebApplication($this);
				$consumer->ConsumeWebService($strWebservice,$arrayParams);
				if ($consumer->GetError() != "")	
				{
					$this->Trace("Error: \"".$consumer->GetError()."\"");		
					$this->SetResult(false);
					return;	
				}
			}
		}
	}
	
	
