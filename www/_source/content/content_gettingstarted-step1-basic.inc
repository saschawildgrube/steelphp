<?php

	class CMyContent extends CContent
	{
		function CallbackRenderContent(&$arrayItems)
		{
			$this->GetWebsite()->IncludeModule("devtools/scaffolder");
			$arrayConfig = array();
			$arrayConfig["preselectedscaffold"] = "websites/basic";
			$scaffolder = new CScaffolderModule($this->GetWebsite(),"",$arrayConfig);
			$arrayItems["SCAFFOLDER"] = $scaffolder->RenderModule();
		}
	}
	
