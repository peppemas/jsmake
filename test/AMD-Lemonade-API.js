//
// Test API script for the AMD Lemonade Server
//

var HOST = "http://localhost:8000"
var response = 0;
var defaultHeaders = {
    "Content-Type": "application/json"
}

function assert(condition) {
    if (!condition) {
        System.exit(-1);
    }
}

// /api/v0/models: list all available models.
response = HttpClient.get(HOST, "/api/v0/models")
assert(response.status === 200)

 // /api/v0/health: check whether a model is loaded and ready to serve.
response = HttpClient.get(HOST, "/api/v0/health")
assert(response.status === 200)

// /api/v0/stats: performance statistics for the generation.
response = HttpClient.get(HOST, "/api/v0/stats")
assert(response.status === 200)

// /api/v0/halt: stop an in-progress generation from make more tokens.
response = HttpClient.get(HOST, "http://localhost:8000/api/v0/halt")
assert(response.status === 200)

// /api/v0/pull: install an LLM by its Lemonade Server Model Name.
HttpClient.reset();
payload = {
    "model_name": "Phi-3.5-Mini-Instruct-Hybrid"
}
response = HttpClient.post(HOST, "/api/v0/pull", defaultHeaders, payload)
assert(response.status === 200)

// /api/v0/load: load a model checkpoint.
HttpClient.reset();
payload = {
    "model_name": "Llama-3.2-1B-Instruct-Hybrid",
    "checkpoint": "amd/Llama-3.2-1B-Instruct-awq-g128-int4-asym-fp16-onnx-hybrid",
    "recipe": "oga-hybrid",
    "reasoning": false,
    "max_prompt_length": 3000
}
response = HttpClient.post(HOST, "/api/v0/load", defaultHeaders, payload)
assert(response.status === 200)

// /api/v0/unload: unload a model checkpoint.
HttpClient.reset();
response = HttpClient.post(HOST, "/api/v0/unload", defaultHeaders, {})
assert(response.status === 200)

/*
### /api/v0/chat/completions: chat completion responses using HTTP chunked transfer encoding.
    POST http://localhost:8000/api/v0/chat/completions
    Content-Type: application/json

{
    "model": "Llama-3.2-1B-Instruct-Hybrid",
    "messages": [],
    "stream": false,
    "logprobs": 0,
    "stop": [],
    "temperature": 0.7,
    "tools": [],
    "max_tokens": 100,
    "max_completion_tokens": 100
}

### /api/v0/responses: responses API using HTTP chunked transfer encoding.
    POST http://localhost:8000/api/v0/responses
    Content-Type: application/json

{
    "input": "this is an input message",
    "model": "Llama-3.2-1B-Instruct-Hybrid",
    "max_output_tokens": 100,
    "temperature": 0.7,
    "stream": false
}

### /api/v0/completions: completion responses using HTTP chunked transfer encoding (if stream=true).
POST http://localhost:8000/api/v0/completions
    Content-Type: application/json
{
    "model": "Phi-3.5-Mini-Instruct-Hybrid",
    "prompt": "Say: this is a test.",
    "stream": false,
    "echo": false,
    "max_tokens": 7,
    "temperature": 0
}
*/