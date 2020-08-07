/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Udp6ServiceBindingENTSTestCase.c

Abstract:

--*/

#include "Udp6ServiceBindingENTSTestCase.h"

//
// Udp6ServiceBinding.CreateChild
//
static EFI_HANDLE *Udp6ServiceBindingCreateChildHandle;
static EFI_STATUS *Udp6ServiceBindingCreateChildStatus;

ENTS_ARG_FIELD    gUdp6ServiceBindingCreateChildArgField[] = {
  {
    POINTER,
    &Udp6ServiceBindingCreateChildHandle
  },
  {
    POINTER,
    &Udp6ServiceBindingCreateChildStatus
  },
  0
};

EFI_STATUS
Udp6ServiceBindingCreateChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6ServiceBinding CreateChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_UDP6_SERVICE_BINDING_PROTOCOL *Udp6ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Udp6ServiceBinding = (EFI_UDP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Udp6ServiceBindingCreateChildStatus = Udp6ServiceBinding->CreateChild (
                                                              Udp6ServiceBinding,
                                                              Udp6ServiceBindingCreateChildHandle
                                                              );
  if (EFI_ERROR (*Udp6ServiceBindingCreateChildStatus)) {
    return EFI_SUCCESS;
  }

  Status = tBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiEntsProtocolGuid,
                  NULL,
                  &NoHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }
  //
  // Walk through each instance need to be tested
  //
  for (HandleIndex = 0; HandleIndex < NoHandles; HandleIndex++) {
    Status = tBS->HandleProtocol (
                    HandleBuffer[HandleIndex],
                    &gEfiEntsProtocolGuid,
                    (VOID **) &Interface
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // match the instance
    //
    if (EntsStrCmp (Interface->ClientName, L"Udp6") == 0) {
      //
      // find it
      //
      Interface->ClientHandle = *Udp6ServiceBindingCreateChildHandle;
	  Status = EFI_SUCCESS;
	  goto Done;
    }
  }

  Status = EFI_NOT_FOUND;
Done:
  if (HandleBuffer != NULL) {
    tBS->FreePool(HandleBuffer);
  }
  return Status;
}

//
// Udp6ServiceBinding.DestroyChild
//
static EFI_HANDLE Udp6ServiceBindingDestroyChildHandle;
static EFI_STATUS *Udp6ServiceBindingDestroyChildStatus;

ENTS_ARG_FIELD    gUdp6ServiceBindingDestroyChildArgField[] = {
  {
    OCTETN,
    &Udp6ServiceBindingDestroyChildHandle
  },
  {
    POINTER,
    &Udp6ServiceBindingDestroyChildStatus
  },
  0
};

EFI_STATUS
Udp6ServiceBindingDestroyChild_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Udp6ServiceBinding DestroyChild Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS   - Operation succeeded.
  EFI_NOT_FOUND - No instance was found.

--*/
{
  EFI_UDP6_SERVICE_BINDING_PROTOCOL *Udp6ServiceBinding;
  UINTN                             NoHandles;
  UINTN                             HandleIndex;
  EFI_HANDLE                        *HandleBuffer;
  EFI_ENTS_PROTOCOL                 *Interface;
  EFI_STATUS                        Status;

  Udp6ServiceBinding = (EFI_UDP6_SERVICE_BINDING_PROTOCOL *) ClientInterface;

  *Udp6ServiceBindingDestroyChildStatus = Udp6ServiceBinding->DestroyChild (
                                                                Udp6ServiceBinding,
                                                                Udp6ServiceBindingDestroyChildHandle
                                                                );
  if (EFI_ERROR (*Udp6ServiceBindingDestroyChildStatus)) {
    return EFI_SUCCESS;
  }

  Status = tBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiEntsProtocolGuid,
                  NULL,
                  &NoHandles,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }
  //
  // Walk through each instance need to be tested
  //
  for (HandleIndex = 0; HandleIndex < NoHandles; HandleIndex++) {
    Status = tBS->HandleProtocol (
                    HandleBuffer[HandleIndex],
                    &gEfiEntsProtocolGuid,
                    (VOID **) &Interface
                    );
    if (EFI_ERROR (Status)) {
      goto Done;
    }
    //
    // match the instance
    //
    if (EntsStrCmp (Interface->ClientName, L"Udp6") == 0) {
      if (NULL == Interface->ClientHandle) {
        continue;
      }
      //
      // find it
      //
      if (EntsCompareMem (Interface->ClientHandle, &Udp6ServiceBindingDestroyChildHandle, sizeof (EFI_HANDLE))) {
        Interface->ClientHandle = NULL;
      }
	  Status = EFI_SUCCESS;
      goto Done;
    }
  }

  Status = EFI_NOT_FOUND;
Done:
  if (HandleBuffer != NULL) {
    tBS->FreePool(HandleBuffer);
  }
  return Status;
}
