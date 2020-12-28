<?php

	class CMyContent extends CContentAdmin
	{
		function CallbackRenderContent(&$arrayItems)
		{
			//$this->GetWebsite()->LoadStringResources("devtools");
			$navigationtree = $this->GetWebsite()->GetNavigationTree("");
			$navigation = new CNavigationElement($this->GetWebsite(),"portfolio");
			$arrayItems["PORTFOLIO"]  = $navigation->RenderNavigationCurrentPathPortfolio($navigationtree);
		}
	}
	
