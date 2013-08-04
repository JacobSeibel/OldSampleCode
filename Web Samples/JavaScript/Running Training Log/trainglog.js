window.onload = init;
function init(){
	if(localStorage.localLog == undefined){
		trainingLog = new Array();
	}
	else{
		trainingLog = JSON.parse(localStorage.localLog);
	}
	currentEntry = 0;
	newOne = true;
	printLog();
}

function TrainingDay(date){
	this.date = date;
	this.distance = "";
	this.time = "";
	this.effort = "";
	this.rating = "";
	this.maxRate = "";
	this.restingRate = "";
	this.weight = "";
	this.sleep = "";
	this.notes = "";
}

function dateChanged(){
	var i = 0;
	newOne = true;
	var dateObject = new Date(document.getElementById("date").value);
	var dateValue = (dateObject.getMonth()+1) + "/" + dateObject.getDate() + "/" + dateObject.getFullYear();
	for(i = 0; i < trainingLog.length; i++){
		if(dateValue == trainingLog[i].date){
			resetEntry(i);
			newOne = false;
			break;
		}
	}
	
	currentEntry = i;
	if(newOne){
		trainingLog[currentEntry] = new TrainingDay(dateValue);
	}
	printLog();
}

function distanceChanged(){
	trainingLog[currentEntry].distance = document.getElementById("runDistance").value;
	printLog();
}

function timeChanged(){
	trainingLog[currentEntry].time = document.getElementById("runTime").value;
	printLog();
}

function ratingChanged(){
	trainingLog[currentEntry].effort = document.getElementById("effortRating").value;
	printLog();
}

function maxRateChanged(){
	trainingLog[currentEntry].maxRate = document.getElementById("maxHeartRate").value;
	printLog();
}

function restingRateChanged(){
	trainingLog[currentEntry].restingRate = document.getElementById("restingHeartRate").value;
	printLog();
}

function weightChanged(){
	trainingLog[currentEntry].weight = document.getElementById("weight").value;
	printLog();
}

function sleepChanged(){
	trainingLog[currentEntry].sleep = document.getElementById("hoursSleep").value;
	printLog();
}

function notesChanged(){
	trainingLog[currentEntry].notes = document.getElementById("notes").value;
	printLog();
}

function printLog(){
	var log = document.getElementById("log");
	var logContents = "<tr><th>Date</th><th>Run Distance</th><th>Run Time</th><th>Effort</th><th>Max heart rate</th><th>Resting heart rate</th><th>Weight</th><th>Sleep</th><th>Notes</th></tr>";
	var i = 0;
	for(i = 0; i < trainingLog.length; i++){
		logContents = logContents + "<tr><td>" + trainingLog[i].date + "</td><td>" + trainingLog[i].distance + "</td><td>" + trainingLog[i].time + "</td><td>" + trainingLog[i].effort + "</td><td>" + trainingLog[i].maxRate + "</td><td>" + trainingLog[i].restingRate + "</td><td>" + trainingLog[i].weight + "</td><td>" + trainingLog[i].sleep + "</td><td>" + trainingLog[i].notes + "</td></tr>";
	}
	log.innerHTML = logContents;
	localStorage.localLog = JSON.stringify(trainingLog);
}

function resetEntry(i){
	trainingLog[i].distance = "";
	trainingLog[i].time = "";
	trainingLog[i].effort = "";
	trainingLog[i].rating = "";
	trainingLog[i].maxRate = "";
	trainingLog[i].restingRate = "";
	trainingLog[i].weight = "";
	trainingLog[i].sleep = "";
	trainingLog[i].notes = "";
}