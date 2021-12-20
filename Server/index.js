var express = require("express");
const { connect } = require("http2");
var app = express();
var server = require("http").Server(app);
var io = require("socket.io")(server);
var sql = require("mssql");
    
app.use(express.static("public"));
app.set("view engine","ejs");
app.set("views", "./views");
// config for your database
var config = {
    user: 'sa',
    password: '88888888',
    server: 'CHUNGDO', 
    database: 'demo' 
};

server.listen(3000);

io.on("connection",function(socket){

    console.log("Co nguoi ket noi: " + socket.id);
    
    socket.on('Trangthai', function(Trangthai) {
        console.log('id: ' + socket.id + ' Trangthai: ' +Trangthai);
        io.sockets.emit('Trangthai', Trangthai);
        });
        
        // connect to your database
        sql.connect(config, function (err) {
    
            if (err) console.log(err);
    
            // create Request object
            var request = new sql.Request();
    
            // query to the database and get the records
    
            request.query("INSERT INTO dbo.test(stt, name) VALUES(2,90)", function (err, recordset) {            
                if  (err) console.log(err)
            });
        });
    socket.on("disconnect", function(){
        console.log(socket.id + " da ngat ket noi");
        // connect to your database
        sql.connect(config, function (err) {
    
            if (err) console.log(err);
    
            // create Request object
            var request = new sql.Request();
    
            // query to the database and get the records
    
            request.query("INSERT INTO dbo.test(stt, name) VALUES(0,00)", function (err, recordset) {            
                if  (err) console.log(err)
            });
        });
    });
});


app.get("/",function(req, res){
    res.render("trangchu");
});