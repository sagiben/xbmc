/*****************************************************************
|
|   Platinum - Light Sample Device
|
| Copyright (c) 2004-2010, Plutinosoft, LLC.
| All rights reserved.
| http://www.plutinosoft.com
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of the GNU General Public License
| as published by the Free Software Foundation; either version 2
| of the License, or (at your option) any later version.
|
| OEMs, ISVs, VARs and other distributors that combine and 
| distribute commercially licensed software with Platinum software
| and do not wish to distribute the source code for the commercially
| licensed software under version 2, or (at your option) any later
| version, of the GNU General Public License (the "GPL") must enter
| into a commercial license agreement with Plutinosoft, LLC.
| licensing@plutinosoft.com
| 
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; see the file LICENSE.txt. If not, write to
| the Free Software Foundation, Inc., 
| 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
| http://www.gnu.org/licenses/gpl-2.0.html
|
****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Neptune.h"
#include "Platinum.h"
#include "PltLightSample.h"

NPT_SET_LOCAL_LOGGER("platinum.test.lightsample")

/*----------------------------------------------------------------------
|   forward references
+---------------------------------------------------------------------*/
extern NPT_UInt8 SCPDXML[];

/*----------------------------------------------------------------------
|   PLT_LightSampleDevice::PLT_LightSampleDevice
+---------------------------------------------------------------------*/
PLT_LightSampleDevice::PLT_LightSampleDevice(const char* FriendlyName, const char* UUID) :	
    PLT_DeviceHost("/", UUID, "urn:schemas-upnp-org:device:SwitchPower:1", FriendlyName)
{
}

/*----------------------------------------------------------------------
|   PLT_LightSampleDevice::~PLT_LightSampleDevice
+---------------------------------------------------------------------*/
PLT_LightSampleDevice::~PLT_LightSampleDevice()
{
}

/*----------------------------------------------------------------------
|   PLT_LightSampleDevice::SetupServices
+---------------------------------------------------------------------*/
NPT_Result
PLT_LightSampleDevice::SetupServices()
{
    NPT_Result res;
    PLT_Service* service = new PLT_Service(
        this,
        "urn:schemas-upnp-org:service:SwitchPower:1", 
        "urn:upnp-org:serviceId:SwitchPower.001",
        "SwitchPower");
    NPT_CHECK_LABEL_FATAL(res = service->SetSCPDXML((const char*)SCPDXML), failure);
    NPT_CHECK_LABEL_FATAL(res = AddService(service), failure);

    service->SetStateVariable("Status", "True");

    return NPT_SUCCESS;
    
failure:
    delete service;
    return res;
}

/*----------------------------------------------------------------------
|   PLT_LightSampleDevice::OnAction
+---------------------------------------------------------------------*/
NPT_Result
PLT_LightSampleDevice::OnAction(PLT_ActionReference&          action,
                                const PLT_HttpRequestContext& context)
{
    NPT_COMPILER_UNUSED(context);

    /* parse the action name */
    NPT_String name = action->GetActionDesc().GetName();
    if (name.Compare("SetTarget") == 0) {
        NPT_String value;
        action->GetArgumentValue("newTargetValue", value);

        PLT_StateVariable* variable = action->GetActionDesc().GetService()->FindStateVariable("Status");
        if (NPT_FAILED(variable->SetValue(value))) {
            action->SetError(402, "Invalid Args");
            return NPT_FAILURE;
        }
        return NPT_SUCCESS;
    } else if (name.Compare("GetStatus") == 0) {
        PLT_StateVariable* variable = action->GetActionDesc().GetService()->FindStateVariable("Status");
        if (variable) {
            action->SetArgumentValue("ResultStatus", variable->GetValue());
            return NPT_SUCCESS;
        }
    }
    
    action->SetError(501, "Action Failed");
    return NPT_FAILURE;
}

NPT_UInt8 SCPDXML[957] =
{
  0x20, 0x20, 0x3C, 0x3F, 0x78, 0x6D, 0x6C, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3D, 0x22, 0x31, 0x2E, 0x30, 
  0x22, 0x20, 0x65, 0x6E, 0x63, 0x6F, 0x64, 0x69, 0x6E, 0x67, 0x3D, 0x22, 0x75, 0x74, 0x66, 0x2D, 0x38, 0x22, 0x20, 0x3F, 
  0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x73, 0x63, 0x70, 0x64, 0x20, 0x78, 0x6D, 0x6C, 0x6E, 0x73, 0x3D, 0x22, 0x75, 
  0x72, 0x6E, 0x3A, 0x73, 0x63, 0x68, 0x65, 0x6D, 0x61, 0x73, 0x2D, 0x75, 0x70, 0x6E, 0x70, 0x2D, 0x6F, 0x72, 0x67, 0x3A, 
  0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x2D, 0x31, 0x2D, 0x30, 0x22, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x73, 0x70, 
  0x65, 0x63, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x6D, 0x61, 0x6A, 0x6F, 0x72, 
  0x3E, 0x31, 0x3C, 0x2F, 0x6D, 0x61, 0x6A, 0x6F, 0x72, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x6D, 0x69, 0x6E, 0x6F, 
  0x72, 0x3E, 0x30, 0x3C, 0x2F, 0x6D, 0x69, 0x6E, 0x6F, 0x72, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x73, 0x70, 
  0x65, 0x63, 0x56, 0x65, 0x72, 0x73, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 0x69, 0x6F, 
  0x6E, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 
  0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x47, 0x65, 0x74, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3C, 0x2F, 0x6E, 
  0x61, 0x6D, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 
  0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 
  0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x52, 0x65, 0x73, 0x75, 0x6C, 0x74, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3C, 
  0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 
  0x6E, 0x3E, 0x6F, 0x75, 0x74, 0x3C, 0x2F, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x20, 0x0D, 0x0A, 
  0x20, 0x20, 0x3C, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 
  0x62, 0x6C, 0x65, 0x3E, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3C, 0x2F, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 
  0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 
  0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 0x6D, 
  0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 
  0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x6E, 0x61, 
  0x6D, 0x65, 0x3E, 0x53, 0x65, 0x74, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x20, 
  0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 
  0x20, 0x20, 0x3C, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 
  0x65, 0x3E, 0x6E, 0x65, 0x77, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x56, 0x61, 0x6C, 0x75, 0x65, 0x3C, 0x2F, 0x6E, 0x61, 
  0x6D, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x69, 
  0x6E, 0x3C, 0x2F, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x72, 
  0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 
  0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x3C, 0x2F, 0x72, 0x65, 0x6C, 0x61, 0x74, 0x65, 0x64, 0x53, 0x74, 0x61, 0x74, 0x65, 
  0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 
  0x6D, 0x65, 0x6E, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x72, 0x67, 0x75, 0x6D, 0x65, 0x6E, 0x74, 0x4C, 
  0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x3E, 0x0D, 0x0A, 0x20, 
  0x20, 0x3C, 0x2F, 0x61, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x4C, 0x69, 0x73, 0x74, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x73, 
  0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x53, 0x74, 0x61, 0x74, 0x65, 0x54, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 
  0x20, 0x3C, 0x73, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x73, 0x65, 0x6E, 0x64, 
  0x45, 0x76, 0x65, 0x6E, 0x74, 0x73, 0x3D, 0x22, 0x79, 0x65, 0x73, 0x22, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x6E, 0x61, 
  0x6D, 0x65, 0x3E, 0x53, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 
  0x20, 0x3C, 0x64, 0x61, 0x74, 0x61, 0x54, 0x79, 0x70, 0x65, 0x3E, 0x62, 0x6F, 0x6F, 0x6C, 0x65, 0x61, 0x6E, 0x3C, 0x2F, 
  0x64, 0x61, 0x74, 0x61, 0x54, 0x79, 0x70, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x73, 0x74, 0x61, 0x74, 
  0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x73, 0x74, 0x61, 0x74, 0x65, 
  0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x73, 0x65, 0x6E, 0x64, 0x45, 0x76, 0x65, 0x6E, 0x74, 0x73, 0x3D, 
  0x22, 0x6E, 0x6F, 0x22, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x54, 0x61, 0x72, 0x67, 0x65, 
  0x74, 0x3C, 0x2F, 0x6E, 0x61, 0x6D, 0x65, 0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x64, 0x61, 0x74, 0x61, 0x54, 0x79, 
  0x70, 0x65, 0x3E, 0x62, 0x6F, 0x6F, 0x6C, 0x65, 0x61, 0x6E, 0x3C, 0x2F, 0x64, 0x61, 0x74, 0x61, 0x54, 0x79, 0x70, 0x65, 
  0x3E, 0x20, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x73, 0x74, 0x61, 0x74, 0x65, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6C, 
  0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x73, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x53, 0x74, 0x61, 0x74, 0x65, 
  0x54, 0x61, 0x62, 0x6C, 0x65, 0x3E, 0x0D, 0x0A, 0x20, 0x20, 0x3C, 0x2F, 0x73, 0x63, 0x70, 0x64, 0x3E
};
