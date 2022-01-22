var lvl;
var lctn;

function getLvl(){
    fetch('http://localhost:8000/getLvl').then(function (response) {
        return response.json();
        }).then(function (text) {
        console.log('GET response:');
        lvl = text.level;  
    });
    return lvl;
}

function getLoc(){
    fetch('http://localhost:8000/getLvl').then(function (response) {
        return response.json();
        }).then(function (text) {
        console.log('GET response:');
        lctn = text.location;  
    });
    return lctn;
}

var strt_dt = Date.now();
var cnt = 0;

function loadPic(lvl) {
    console.log("Here");
    var img = document.getElementById('bin_img');
    // var lvl = getLvl();
    var al = 45 - lvl;
    var pcnt = al / 35;
    var end_dt = Date.now();
    var diff = end_dt - strt_dt;
    if(pcnt == 0){
        img.src = "img/dbin.png";
        cnt = 0;
    }
    else if (pcnt > 0 && pcnt <= 0.25) {
        console.log("Here");
        img.src = "img/dbin25.png";
        cnt = 0;
    }
    else if (pcnt > 0.25 && pcnt <= 0.5) {
        img.src = "img/dbin50.png";
        cnt = 0;
    }
    else if (pcnt > 0.5 && pcnt <= 0.75) {
        img.src = "img/dbin75.png";
        cnt = 0;
    }
    else if (pcnt > 0.75) {
        img.src = "img/dbin100.png";
        var dt_diff = new Date(diff);
        console.log(dt_diff.getMinutes());
        var loc = getLoc();
        console.log("Loc: ", loc);
        if(pcnt >= 1 && cnt == 0 && loc) {
            var t1 = "The dustbin at location: ";
            var t2 = " is full. Please send someone to empty it";
            var al = t1.concat(loc, t2);
            console.log(al);
            alert(al);
            cnt = 1;
            strt_dt = Date.now();
        }
        if(pcnt >= 1 && cnt == 1 && dt_diff.getMinutes() == 10) {
            var t1 = "The dustbin at location: ";
            var t2 = " is still full. Kindly follow through the request";
            var al = t1.concat(loc, t2);
            alert(al);
            strt_dt = Date.now();
        }
    }    
}

function getData() {
    return Math.random();
}





