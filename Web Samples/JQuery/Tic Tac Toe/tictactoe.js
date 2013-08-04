var row0 = new Array();
var row1 = new Array();
var row2 = new Array();
var player = 1;
var playerxwins = 0;
var playerowins = 0;
var turnNumber = 0;

$(document).ready(function(){
  $("td").mouseover(function(){
	if($("#"+this.id).html() == "&nbsp;"){
		$("#"+this.id).css("background-color","lightblue");
	}
	else{
		$("#"+this.id).css("background-color","red");
	}
  });
  
  $("td").mouseout(function(){
	$("#"+this.id).css("background-color","ghostwhite");
  });

  $("td").click(function(){
	if($("#"+this.id).html() != "&nbsp;"){
		alert("There is already a symbol in this square.");
	}
	else if(player == 1){
		$("#"+this.id).text("X");
		eval("row"+this.id.charAt(4)+"[this.id.charAt(5)] = 1;");
		player++;
		win("1", this.id);
		turnNumber++;
	}
	else{
		$("#"+this.id).text("O");
		eval("row"+this.id.charAt(4)+"[this.id.charAt(5)] = 0;");
		player--;
		win("0", this.id);
		turnNumber++;
	}
	if(turnNumber == 9){
		alert("The game is a tie!")
		reset();
	}
  });
  
	function win(player, cell){
		var row = cell.charAt(4);
		var col = cell.charAt(5);
		var win = 0;
		
		if((row == 0 && col == 0) || (row == 2 && col == 2) || (row == 1 && col == 1)){
			if(row0[0] + row1[1] + row2[2] == 3*player){
				win = 1;
			}
		}
		if((row == 0 && col == 2) || (row == 2 && col == 0) || (row == 1 && col == 1)){
			if(row0[2] + row1[1] + row2[0] == 3*player){
				win = 1;
			}
		}
		if(row == 0){
			if(row0[0] + row0[1] + row0[2] == 3*player){
				win = 1;
			}
		}
		else if(row == 1){
			if(row1[0] + row1[1] + row1[2] == 3*player){
				win = 1;
			}
		}
		else if(row == 2){
			if(row2[0] + row2[1] + row2[2] == 3*player){
				win = 1;
			}
		}
		if(col == 0){
			if(row0[0] + row1[0] + row2[0] == 3*player){
				win = 1;
			}
		}
		else if(col == 1){
			if(row0[1] + row1[1] + row2[1] == 3*player){
				win = 1;
			}
		}
		else if(col == 2){
			if(row0[2] + row1[2] + row2[2] == 3*player){
				win = 1;
			}
		}
		
		if(win == 1){
			if(player == 1){
				alert("X has won!");
				playerxwins++;
			}
			else{
				alert("O has won!");
				playerowins++;
			}
			reset();
		}
	}
  
	function reset(){
		$("#board").slideToggle("fast");
		row0 = new Array();
		row1 = new Array();
		row2 = new Array();
		player = 1;
		turnNumber = 0;
		$("#cell00").html("&nbsp;");
		$("#cell01").html("&nbsp;");
		$("#cell02").html("&nbsp;");
		$("#cell10").html("&nbsp;");
		$("#cell11").html("&nbsp;");
		$("#cell12").html("&nbsp;");
		$("#cell20").html("&nbsp;");
		$("#cell21").html("&nbsp;");
		$("#cell22").html("&nbsp;");
		$("#board").slideToggle("slow");
		$("#xWins").text(playerxwins);
		$("#oWins").text(playerowins);
	}
});