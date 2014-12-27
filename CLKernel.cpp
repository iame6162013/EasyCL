// Copyright Hugh Perkins 2013 hughperkins at gmail
//
// This Source Code Form is subject to the terms of the Mozilla Public License, 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

#include <stdexcept>
using namespace std;

#include "CLKernel.h"
#include "CLArrayFloat.h"
#include "CLArrayInt.h"
#include "CLArray.h"

CLKernel *CLKernel::input( CLArray *clarray1d ) {
    assert( clarray1d != 0 );
    if( !clarray1d->isOnDevice() ) {
        clarray1d->moveToDevice();
    }
    if( clarray1d->isOnHost() ) {
        clarray1d->deleteFromHost();
    }
    cl_mem *devicearray = clarray1d->getDeviceArray();
    error = clSetKernelArg( kernel, nextArg, sizeof(cl_mem), devicearray );
    openclhelper->checkError(error);
    nextArg++;
    return this;
}

CLKernel *CLKernel::output( CLArray *clarray1d ) {
    assert( clarray1d != 0 );
    if( clarray1d->isOnHost() ) {
        clarray1d->deleteFromHost();
    }
    if( !clarray1d->isOnDevice() ) {
        clarray1d->createOnDevice();
    }
    assert( clarray1d->isOnDevice() && !clarray1d->isOnHost() );
    error = clSetKernelArg( kernel, nextArg, sizeof(cl_mem), (clarray1d->getDeviceArray()) );
    openclhelper->checkError(error);
    nextArg++;  
    return this;      
}

CLKernel *CLKernel::inout( CLArray *clarray1d ) {
    assert( clarray1d != 0 );
    if( !clarray1d->isOnDevice() ) {
        clarray1d->moveToDevice();
    }
    if( clarray1d->isOnHost() ) {
        clarray1d->deleteFromHost();
    }
    cl_mem *devicearray = clarray1d->getDeviceArray();
    error = clSetKernelArg( kernel, nextArg, sizeof(cl_mem), devicearray );
    openclhelper->checkError(error);
    nextArg++;
    return this;
}

CLKernel *CLKernel::input( CLWrapper *wrapper ) {
    assert( wrapper != 0 );
    if( !wrapper->isOnDevice() ) {
        throw std::runtime_error("need to copyToDevice() before calling kernel->input");
    }
    cl_mem *devicearray = wrapper->getDeviceArray();
    error = clSetKernelArg( kernel, nextArg, sizeof(cl_mem), devicearray );
    openclhelper->checkError(error);
    nextArg++;
    return this;
}

CLKernel *CLKernel::output( CLWrapper *wrapper ) {
    assert( wrapper != 0 );
    if( !wrapper->isOnDevice() ) {
        wrapper->createOnDevice();
    }
    error = clSetKernelArg( kernel, nextArg, sizeof(cl_mem), (wrapper->getDeviceArray()) );
    openclhelper->checkError(error);
    nextArg++;
    return this;      
}

