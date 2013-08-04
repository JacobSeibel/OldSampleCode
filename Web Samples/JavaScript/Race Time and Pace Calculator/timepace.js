
function distChanged(){	
	var distance = document.getElementById("raceDistance").value;
	var pace = document.getElementById("pace").value;
	if(!(isNaN(distance) || isNaN(pace)) && !(distance == "") && !(pace == "")){
		document.getElementById("totalTime").value= (distance/pace)*60;
	}
}
function timeChanged(){
	var time = document.getElementById("totalTime").value;
	var distance = document.getElementById("raceDistance").value;
	if(!(isNaN(time) || isNaN(distance)) && !(time == "") && !(distance == "")){
		document.getElementById("pace").value= (distance/(time/60));
		paceChanged();
	}
}
function paceChanged(){
	var distance = document.getElementById("raceDistance").value;
	var pace = document.getElementById("pace").value;
	var desc = document.getElementById("description");
	if(!(isNaN(pace) || isNaN(distance)) && !(pace == "") && !(distance == "")){
		document.getElementById("totalTime").value = (distance/pace)*60;
	}
	var message = "";
	if(pace >= 12){
		message = "I'd leave you a message, but you've probably already run along.";
	}
	if(pace < 12){
		message = "Wooh!  You should try out for your rec league running team!";
	}
	if(pace < 9){
		message = "You're almost average. Like Count Chocula.";
	}
	if(pace < 6){
		message = "Come on, man! I've known cheese wheels faster than you!";
	}
	if(pace < 3){
		message = "Are you walking? Do you know how to run?";
	}
	desc.innerHTML = message;
}
function unitsChanged(){
	if(document.getElementById("units").value == "miles"){
		document.getElementById("raceDistance").value = (document.getElementById("raceDistance").value * 0.621371);
	}
	else{
		document.getElementById("raceDistance").value = (document.getElementById("raceDistance").value * 1.60934);
	}
	distChanged();
}