var http = require('http')

//make the request object
var request = http.request({
    'host': '171.107.188.173',
    'port': 80,
    'path': '/',
    'method': 'GET'
})

//assign callbacks
request.on('response', function (response) {
    console.log('Response status code:' + response.statusCode)

    response.on('data', function (data) {
        console.log('Body: ' + data)
    })
})

request.end()
