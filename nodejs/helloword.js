var http = require('http')
var now_ms = Date.now()
var opt = {
    host: '10.14.36.100',
    port: '8080',
    method: 'get',//这里是发送的方法
    path: 'http://d1.weather.com.cn/sk_2d/101280601.html?_=' + now_ms,
    headers: {
        //这里放期望发送出去的请求头
        'Referer': 'http://www.weather.com.cn/weather1d/101280601.shtml'
    }
}

console.log(opt.path)

http.get(opt, function (res) {
    var source = ""
    //通过 get 请求获取网页代码 source
    res.on('data', function (data) {
        source += data
    })
    //获取到数据 source，我们可以对数据进行操作了!
    res.on('end', function () {
        console.log(source)
        //这将输出很多的 html 代码
    })
}).on('error', function () {
    console.log("获取数据出现错误")
})
