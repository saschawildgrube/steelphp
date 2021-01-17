<?php

	class CMyContent extends CContent
	{
		function OnRenderContent(&$arrayItems)
		{
			$this->GetWebsite()->IncludeModule("devtools/scaffolder");
			$scaffolder = new CScaffolderModule($this->GetWebsite());
			$arrayItems["SCAFFOLDER"] = $scaffolder->RenderModule();
		}
	}
	
