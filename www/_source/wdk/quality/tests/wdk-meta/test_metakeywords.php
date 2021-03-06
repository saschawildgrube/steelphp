<?php
	
	require_once(GetWDKDir()."wdk_unittest.inc");

	class CTest extends CUnitTest
	{
		function __construct()
		{
			parent::__construct("Test Meta Keywords");
		}
		
		function OnInit()
		{
			parent::OnInit(); 
			//$this->SetActive(false);
			return true;
		}
		
		function TestCase_MetaKeywords(
			$strURL,
			$arrayExpected)
		{ 
			$this->Trace("");
			$this->Trace("TestCase_MetaKeywords");
			$this->TestCase_CheckURL($strURL,$arrayExpected);
		}
		
		function OnTest()
		{
			parent::OnTest();
			$this->SetResult(true);

			$arrayExpected = array("defaultkeyword1","defaultkeyword2","specifickeyword1","specifickeyword2");

			$strURL = "http://".GetRootURL()."quality/testwebsite/?content=test-meta1";
			$this->TestCase_MetaKeywords(
				$strURL,
				$arrayExpected);

		}
		
		function OnCleanup()
		{
			parent::OnCleanup();
			return true;
		}
		 
		
	} 
	
	
		


		
