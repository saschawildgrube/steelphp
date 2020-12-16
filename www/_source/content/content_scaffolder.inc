<?php

	class CMyContent extends CContent
	{
		function CallbackRenderContent(&$arrayItems)
		{
			$this->GetWebsite()->IncludeModule("devtools/scaffolder");
			$scaffolder = new CScaffolderModule($this->GetWebsite());
			$arrayItems["SCAFFOLDER"] = $scaffolder->RenderModule();
		}
	}
	
