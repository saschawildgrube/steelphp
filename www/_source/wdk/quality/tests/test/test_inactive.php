<?php
	
	class CTest extends CUnitTest
	{
		function __construct()
		{
			parent::__construct("Test CUnitTest");
		}
		
		function OnInit()
		{
			parent::OnInit();
			return true;
		}
		
		function OnTest()
		{
			parent::OnTest();
	
			$this->Trace("This is an inactive test!");
			$this->SetActive(false);
	
			$this->SetResult(true);	
		}
		
		function OnCleanup()
		{
			parent::OnCleanup();
			return true;
		}
		
		
	}
	
			
