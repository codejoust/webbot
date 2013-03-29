//

// uncomment for production, comment for dev
if (!console){
    console = {log: function(arg){}};
}
if (!window.opts){
  window.opts = {};
}

function issue_command(command, args){
  $status = $('#status');
  $.post('./reciever.php', {command: command, args: args}, function(res){
    $status.html('sent command: ' + command);
    setTimeout(function(){
      $status.html('');
    }, 400);
  });
}

function run_poll(){
  $.get('poll.php?type=' + (window.opts.poll_type || ''), function(res, succ){
    console.log('poll done: ' + succ);
    console.log('"' + res + '"');
    if (res){
      var input = res.split(':');
      console.log(input);
      window[input[0]](input[1]);
    }
    if (succ == 'success'){
      run_poll();
    }
  });
}

$(function(){
  $('.command').bind('click', function(){
    var $t = $(this);
    if ($t.data('cmd')){
      issue_command($t.data('cmd'));
    }
    return false;
  });
  run_poll();
  
});
