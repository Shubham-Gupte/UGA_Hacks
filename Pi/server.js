var express = require('express');
var app = express();
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({extended:true}));
app.use(express.static(__dirname));
const PORT = 5000;

app.set('port', (process.env.PORT || 5000));

app.get("/", function(req, res){
  res.sendFile('index.html');
});

app.get("/alarm", function(req, res){
  res.sendFile('lawl.html',{root:__dirname});
});

app.post("/pi", function(req, res){
  res.send('done');
});
app.listen(app.get('port'),function(){
  console.log("node app is running at localhost:" + app.get('port'));
});
