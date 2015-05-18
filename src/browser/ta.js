
var ta = {
    textDelayMS : 50,
    instructions : {
        say: function(iMessage) {
            console.log('Saying: "' + iMessage + '"');
            var container = $('<p>');
            container.appendTo('body');
            var i = 0;
            var interval = setInterval(function() {
                if (i <= iMessage.length) {
                    container.html(iMessage.slice(0, i));
                    i++;
                }
                else {
                    clearInterval(interval);
                }
            }, ta.textDelayMS);
        }
        ,
        clearScreen: function() {
            console.log('Clearing the screen');
            $('body').html('');
        }
    }
}

function onPageLoaded()
{
    ta.instructions.say('Welcome to TextAdventure (Copyright Albob 2015)');
    ta.instructions.clearScreen();
    ta.instructions.say('You enter a kitchen.');
    ta.instructions.say('The air is filthy.');
}

