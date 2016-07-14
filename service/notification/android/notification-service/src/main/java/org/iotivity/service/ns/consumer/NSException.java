//******************************************************************
//
// Copyright 2016 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

package org.iotivity.service.ns.consumer;

public class NSException extends Exception {

    private NSErrorCode errorCode;

    public NSException(NSErrorCode errorCode, String errMessage) {
        super(errMessage + " " + errorCode.toString());
        this.errorCode = errorCode;
    }

    private NSException(String error, String errMessage) {
        super(errMessage + " " + error);
        this.errorCode = NSErrorCode.get(error);
    }

    public NSErrorCode getErrorCode() {
        return errorCode;
    }

    private static void addStackTrace(Throwable throwable,
                                      String file,
                                      String functionName,
                                      int line) {
        StackTraceElement[] stack = throwable.getStackTrace();
        StackTraceElement[] newStack = new StackTraceElement[stack.length + 1];

        System.arraycopy(stack, 0, newStack, 1, stack.length);
        newStack[0] = new StackTraceElement("<native>", functionName, file, line);
        throwable.setStackTrace(newStack);
    }

    private void setNativeExceptionLocation(String file, String functionName, int line) {
        NSException.addStackTrace(this, file, functionName, line);
    }

}