
var ta = {
    instructions : {
        say: function(iMessage) {
            console.log('Saying: "' + iMessage + '"');
            $('<p>').html(iMessage).appendTo('body');
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

