;(function() {
  window.onload = function() {
    var preloading = document.querySelector('.page-preloading');
    preloading.classList.add('loading-done');
  };
})();

/**
 * @license
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * A component handler interface using the revealing module design pattern.
 * More details on this design pattern here:
 * https://github.com/jasonmayes/mdl-component-design-pattern
 *
 * @author Jason Mayes.
 */
var componentHandler={upgradeDom:function(e,n){},upgradeElement:function(e,n){},upgradeElements:function(e){},upgradeAllRegistered:function(){},registerUpgradedCallback:function(e,n){},register:function(e){},downgradeElements:function(e){}};componentHandler=function(){"use strict";function e(e,n){for(var t=0;t<u.length;t++)if(u[t].className===e)return"undefined"!=typeof n&&(u[t]=n),u[t];return!1}function n(e){var n=e.getAttribute("data-upgraded");return null===n?[""]:n.split(",")}function t(e,t){var r=n(e);return-1!==r.indexOf(t)}function r(n,t){if("undefined"==typeof n&&"undefined"==typeof t)for(var a=0;a<u.length;a++)r(u[a].className,u[a].cssClass);else{var s=n;if("undefined"==typeof t){var d=e(s);d&&(t=d.cssClass)}for(var l=document.querySelectorAll("."+t),c=0;c<l.length;c++)o(l[c],s)}}function o(r,o){if(!("object"==typeof r&&r instanceof Element))throw new Error("Invalid argument provided to upgrade MDL element.");var a=n(r),s=[];if(o)t(r,o)||s.push(e(o));else{var d=r.classList;u.forEach(function(e){d.contains(e.cssClass)&&-1===s.indexOf(e)&&!t(r,e.className)&&s.push(e)})}for(var l,c=0,i=s.length;i>c;c++){if(l=s[c],!l)throw new Error("Unable to find a registered component for the given class.");a.push(l.className),r.setAttribute("data-upgraded",a.join(","));var f=new l.classConstructor(r);f[m]=l,p.push(f);for(var g=0,v=l.callbacks.length;v>g;g++)l.callbacks[g](r);l.widget&&(r[l.className]=f);var w;"CustomEvent"in window&&"function"==typeof window.CustomEvent?w=new Event("mdl-componentupgraded",{bubbles:!0,cancelable:!1}):(w=document.createEvent("Events"),w.initEvent("mdl-componentupgraded",!0,!0)),r.dispatchEvent(w)}}function a(e){Array.isArray(e)||(e=e instanceof Element?[e]:Array.prototype.slice.call(e));for(var n,t=0,r=e.length;r>t;t++)n=e[t],n instanceof HTMLElement&&(o(n),n.children.length>0&&a(n.children))}function s(n){var t="undefined"==typeof n.widget&&"undefined"==typeof n.widget,r=!0;t||(r=n.widget||n.widget);var o={classConstructor:n.constructor||n.constructor,className:n.classAsString||n.classAsString,cssClass:n.cssClass||n.cssClass,widget:r,callbacks:[]};if(u.forEach(function(e){if(e.cssClass===o.cssClass)throw new Error("The provided cssClass has already been registered: "+e.cssClass);if(e.className===o.className)throw new Error("The provided className has already been registered")}),n.constructor.prototype.hasOwnProperty(m))throw new Error("MDL component classes must not have "+m+" defined as a property.");var a=e(n.classAsString,o);a||u.push(o)}function d(n,t){var r=e(n);r&&r.callbacks.push(t)}function l(){for(var e=0;e<u.length;e++)r(u[e].className)}function c(e){if(e){var n=p.indexOf(e);p.splice(n,1);var t=e.element_.getAttribute("data-upgraded").split(","),r=t.indexOf(e[m].classAsString);t.splice(r,1),e.element_.setAttribute("data-upgraded",t.join(","));var o;"CustomEvent"in window&&"function"==typeof window.CustomEvent?o=new Event("mdl-componentdowngraded",{bubbles:!0,cancelable:!1}):(o=document.createEvent("Events"),o.initEvent("mdl-componentdowngraded",!0,!0)),e.element_.dispatchEvent(o)}}function i(e){var n=function(e){p.filter(function(n){return n.element_===e}).forEach(c)};if(e instanceof Array||e instanceof NodeList)for(var t=0;t<e.length;t++)n(e[t]);else{if(!(e instanceof Node))throw new Error("Invalid argument provided to downgrade MDL nodes.");n(e)}}var u=[],p=[],m="mdlComponentConfigInternal_";return{upgradeDom:r,upgradeElement:o,upgradeElements:a,upgradeAllRegistered:l,registerUpgradedCallback:d,register:s,downgradeElements:i}}(),componentHandler.ComponentConfigPublic,componentHandler.ComponentConfig,componentHandler.Component,componentHandler.upgradeDom=componentHandler.upgradeDom,componentHandler.upgradeElement=componentHandler.upgradeElement,componentHandler.upgradeElements=componentHandler.upgradeElements,componentHandler.upgradeAllRegistered=componentHandler.upgradeAllRegistered,componentHandler.registerUpgradedCallback=componentHandler.registerUpgradedCallback,componentHandler.register=componentHandler.register,componentHandler.downgradeElements=componentHandler.downgradeElements,window.componentHandler=componentHandler,window.componentHandler=componentHandler,window.addEventListener("load",function(){"use strict";"classList"in document.documentElement&&"querySelector"in document&&"addEventListener"in window&&"forEach"in Array.prototype?(document.documentElement.classList.add("mdl-js"),componentHandler.upgradeAllRegistered()):(componentHandler.upgradeElement=function(){},componentHandler.register=function(){})});

/**
 * @license
 * Copyright 2015 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
!function(){"use strict";var s=function(s){this.element_=s,this.init()};window.MaterialSpinner=s,s.prototype.Constant_={MDL_SPINNER_LAYER_COUNT:4},s.prototype.CssClasses_={MDL_SPINNER_LAYER:"mdl-spinner__layer",MDL_SPINNER_CIRCLE_CLIPPER:"mdl-spinner__circle-clipper",MDL_SPINNER_CIRCLE:"mdl-spinner__circle",MDL_SPINNER_GAP_PATCH:"mdl-spinner__gap-patch",MDL_SPINNER_LEFT:"mdl-spinner__left",MDL_SPINNER_RIGHT:"mdl-spinner__right"},s.prototype.createLayer=function(s){var t=document.createElement("div");t.classList.add(this.CssClasses_.MDL_SPINNER_LAYER),t.classList.add(this.CssClasses_.MDL_SPINNER_LAYER+"-"+s);var e=document.createElement("div");e.classList.add(this.CssClasses_.MDL_SPINNER_CIRCLE_CLIPPER),e.classList.add(this.CssClasses_.MDL_SPINNER_LEFT);var a=document.createElement("div");a.classList.add(this.CssClasses_.MDL_SPINNER_GAP_PATCH);var i=document.createElement("div");i.classList.add(this.CssClasses_.MDL_SPINNER_CIRCLE_CLIPPER),i.classList.add(this.CssClasses_.MDL_SPINNER_RIGHT);for(var _=[e,a,i],n=0;n<_.length;n++){var r=document.createElement("div");r.classList.add(this.CssClasses_.MDL_SPINNER_CIRCLE),_[n].appendChild(r)}t.appendChild(e),t.appendChild(a),t.appendChild(i),this.element_.appendChild(t)},s.prototype.createLayer=s.prototype.createLayer,s.prototype.stop=function(){this.element_.classList.remove("is-active")},s.prototype.stop=s.prototype.stop,s.prototype.start=function(){this.element_.classList.add("is-active")},s.prototype.start=s.prototype.start,s.prototype.init=function(){if(this.element_){for(var s=1;s<=this.Constant_.MDL_SPINNER_LAYER_COUNT;s++)this.createLayer(s);this.element_.classList.add("is-upgraded")}},componentHandler.register({constructor:s,classAsString:"MaterialSpinner",cssClass:"mdl-js-spinner",widget:!0})}();
