<?php
/*
 * softflowd.priv.inc
 *
 * part of pfSense (https://www.pfsense.org)
 * Copyright (c) 2017-2020 Rubicon Communications, LLC (Netgate)
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

global $priv_list;

$priv_list['page-services-softflowd'] = array();
$priv_list['page-services-softflowd']['name'] = "WebCfg - Services: softflowd package";
$priv_list['page-services-softflowd']['descr'] = "Allow access to softflowd package GUI";
$priv_list['page-services-softflowd']['match'] = array();

$priv_list['page-services-softflowd']['match'][] = "pkg.php?xml=softflowd.xml*";
$priv_list['page-services-softflowd']['match'][] = "pkg_edit.php?xml=softflowd.xml*";

?>