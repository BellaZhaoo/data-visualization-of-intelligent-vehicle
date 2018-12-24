/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

var PROTO_PATH = __dirname + '/../../protos/auto_interface.proto';

var grpc = require('grpc');
var hello_proto = grpc.load(PROTO_PATH).autointerface;

//

//
/**
 * Implements the SayHello RPC method.
 */
//

//
/*function sayHello(call, callback) {
  callback(null, {message: 'Hello ' + call.request.name});
}
*/

function sayHello(call, callback) {
  callback(null, {message: Math.random() + call.request.name});
}

/**
 * Starts an RPC server that receives requests for the Greeter service at the
 * sample server port
 */

function main() {
  var server = new grpc.Server();
  server.addService(hello_proto.AutoInterface.service, {sayHello: sayHello});
  server.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
  server.start();
}

main();
