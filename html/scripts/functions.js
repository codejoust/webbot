function status(status){
	$('#poll-status').html(status).fadeIn('fast');
	setTimeout(function(){
		$('#poll-status').fadeOut('fast');
	},1000);
}

function alert(text){
	$('#header').html(text).css('font-size','10px').show().animate({'font-50px': 'size'}, 1000, function(){
		$(this).hide();
	})
}

function flashy(){
	$('body').css('background', '#eee');
	setTimeout(function(){
		$('body').css('background', '#fff');
	}, 200);
}

function play_audio(url){
	var snd = document.getElementById('snd');
	if (!snd){
		snd = document.createElement('audio');
		document.body.appendChild(snd);
	}
	snd.src = url;
	snd.load();
	
	//snd.currentTime = 0;
	snd.play();
}

function greet(text){
	//text = 'Hello-Im-' + text;
    play_audio('http://translate.google.com/translate_tts?tl=en&q='+text);
}

function speak(text){
	greet(text);
}

function play_sound(type){
	var files_mapping = {
		alarm: 'alarma.wav',
		alarm1: 'alarma.wav',
		click: 'click.wav',
		tstorm: 'tstorm.mp3',
		macup: 'Startup1.wav'
	}
	if (files_mapping[type]){
		status("playing sound " + type);
		play_audio('sounds/' + files_mapping[type]);
	}
}