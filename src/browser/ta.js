
var ta = {
    instrQueue : [],
    instructions : {
        say: function(iMessage, iTextDelayMS, iTextPauseMS) {

            var textDelayMS = (iTextDelayMS !== undefined) ? iTextDelayMS : 40;
            var textPauseMS = (iTextPauseMS !== undefined) ? iTextPauseMS : 400;

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
                    setTimeout(function() {
                        ta.nextInstruction();
                    }, textPauseMS);
                }
            }, textDelayMS);
        }
        ,
        clearScreen: function() {
            console.log('Clearing the screen');
            $('body').html('');
            ta.nextInstruction();
        }
    }
    ,
    pushInstruction : function(iName, iParams)  {
        console.log('Pushing instruction "' + iName + '" with params "' + iParams + '"');
        console.log(ta.instrQueue);
        ta.instrQueue.push([iName, iParams]);
    },
    nextInstruction : function() {
        var instr = ta.instrQueue.shift();
        var instrName = instr[0];
        var instrParams = instr[1];
        var func = ta.instructions[instrName];

        console.log('Popping instruction "' + instrName + '" with params "' + instrParams + '"');
        console.log(ta.instrQueue);

        if (instrParams && instrParams.length > 0) {
            func.apply(null, instr[1]);
        }
        else {
            func();
        }
    }
}

function onPageLoaded()
{
    ta.pushInstruction('say', ['Welcome to TextAdventure (Copyright Albob 2015)', 40, 1000]);
    ta.pushInstruction('clearScreen');
    ta.pushInstruction('say', ['You wake up in a kitchen.']);
    ta.pushInstruction('say', ['The air is filthy.']);
    ta.pushInstruction('say', ['You check your pockets.']);
    ta.pushInstruction('say', ['.......', 160]);
    ta.pushInstruction('say', ['Nothing.']);
    ta.nextInstruction();
}
