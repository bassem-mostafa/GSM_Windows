// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef GSM_WINDOWS

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include "../../GSM_Internal.h"
    #include "GSM_Windows_Port.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

GSM_Status_t GSM_IsValid( GSM_t GSM )
{
    GSM_Status_t GSM_Status = GSM_Status_Error;
    do
    {
        GSM_Trace( "%s( GSM=GSM_%d )", __FUNCTION__, GSM );
        switch ( GSM )
        {
            case GSM_1:
                GSM_Status = GSM_Status_Success;
                break;
            default:
                GSM_Error( "Invalid Argument" );
                GSM_Status = GSM_Status_Error;
                break;
        }
    }
    while ( 0 );
    return GSM_Status;
}

GSM_Status_t GSM_Instance_Initialize( GSM_Instance_t * GSM_Instance )
{
    GSM_Status_t GSM_Status = GSM_Status_Error;
    do
    {
        GSM_Trace( "%s( GSM_Instance=%p )", __FUNCTION__, GSM_Instance );
        if ( ( GSM_Status = GSM_Instance_IsValid( GSM_Instance ) ) != GSM_Status_Success )
        {
            break;
        }
        for ( GSM_t GSM = GSM_1; GSM < GSM_NUMBER_OF_INSTANCES; ++GSM )
        {
            if ( GSM_Instance == &GSM_Context.Instance[ GSM ] )
            {
                GSM_Instance->GSM = GSM;
                break;
            }
        }
        GSM_BC92_Status_t GSM_BC92_Status = GSM_BC92_Status_Error;
        switch ( GSM_Instance->GSM )
        {
            case GSM_1:
                GSM_Instance->BC92.Serial = UART_1;
                GSM_Instance->BC92.OnComplete = GSM_BC92_Callback_OnComplete;
                if ( ( GSM_BC92_Status = GSM_BC92_Initialize( &GSM_Instance->BC92 ) ) != GSM_BC92_Status_Success )
                {
                    GSM_Status = GSM_Status_Error;
                    break;
                }
                GSM_Status = GSM_Status_Success;
                break;
            default:
                GSM_Status = GSM_Status_Error;
                break;
        }
    }
    while ( 0 );
    return GSM_Status;
}

GSM_Status_t GSM_Instance_DeInitialize( GSM_Instance_t * GSM_Instance )
{
    GSM_Status_t GSM_Status = GSM_Status_Error;
    do
    {
        GSM_Trace( "%s( GSM_Instance=%p )", __FUNCTION__, GSM_Instance );
        if ( ( GSM_Status = GSM_Instance_IsValid( GSM_Instance ) ) != GSM_Status_Success )
        {
            break;
        }
        GSM_BC92_Status_t GSM_BC92_Status = GSM_BC92_Status_Error;
        switch ( GSM_Instance->GSM )
        {
            case GSM_1:
                if ( ( GSM_BC92_Status = GSM_BC92_DeInitialize( &GSM_Instance->BC92 ) ) != GSM_BC92_Status_Success )
                {
                    GSM_Status = GSM_Status_Error;
                    break;
                }
                GSM_Status = GSM_Status_Success;
                break;
            default:
                GSM_Status = GSM_Status_Error;
                break;
        }
    }
    while ( 0 );
    return GSM_Status;
}

GSM_Status_t GSM_Instance_Cycle( GSM_Instance_t * GSM_Instance )
{
    GSM_Status_t GSM_Status = GSM_Status_Error;
    do
    {
        GSM_Trace( "%s(GSM_Instance=%p)", __FUNCTION__, GSM_Instance );
        if ( ( GSM_Status = GSM_Instance_IsValid( GSM_Instance ) ) != GSM_Status_Success )
        {
            break;
        }
        GSM_BC92_Status_t GSM_BC92_Status = GSM_BC92_Status_Error;
        switch ( GSM_Instance->GSM )
        {
            case GSM_1:
                if ( ( GSM_BC92_Status = GSM_BC92_Cycle( &GSM_Instance->BC92 ) ) != GSM_BC92_Status_Success )
                {
                    GSM_Status = GSM_Status_Error;
                    break;
                }
                GSM_Status = GSM_Status_Success;
                break;
            default:
                GSM_Status = GSM_Status_Error;
                break;
        }
    }
    while ( 0 );
    return GSM_Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* GSM_WINDOWS */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
