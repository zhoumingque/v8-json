#include <node.h>

using namespace v8;

void parse(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (!args[0]->IsString()){
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Param is Not String!")));
    return;
  }
  
  MaybeLocal<Value> json = JSON::Parse(isolate,args[0]->ToString());
  if (json.IsEmpty()){
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Param is Not JSON String!")));
    return;
  }
  Local<Value> value = json.ToLocalChecked();
  args.GetReturnValue().Set(value);
}

void stringify(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (!args[0]->IsObject()){
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Param is Not Object!")));
    return;
  }
  MaybeLocal<String> str = JSON::Stringify(Isolate::GetCurrent()->GetCurrentContext(),args[0]->ToObject());
  Local<String> value = str.ToLocalChecked();
  args.GetReturnValue().Set(value);
}

void Init(Local<Object> exports, Local<Object> module){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  Local<FunctionTemplate> p = FunctionTemplate::New(isolate, parse);
  Local<FunctionTemplate> s = FunctionTemplate::New(isolate, stringify);
  exports->Set(String::NewFromUtf8(isolate,"parse"), p->GetFunction());
  exports->Set(String::NewFromUtf8(isolate,"stringify"), s->GetFunction());
}

NODE_MODULE(vjson, Init);