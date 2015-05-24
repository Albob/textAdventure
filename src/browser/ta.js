
var ta = {
    rawScript : '',
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
                        ta.doNextInstruction();
                    }, textPauseMS);
                }
            }, textDelayMS);
        }
        ,
        clearScreen: function() {
            console.log('Clearing the screen');
            $('body').html('');
            ta.doNextInstruction();
        }
    }
    ,
    queueInstruction : function(iName, iParams)  {
        console.log('Pushing instruction "' + iName + '" with params "' + iParams + '"');
        console.log(ta.instrQueue);
        ta.instrQueue.push([iName, iParams]);
    }
    ,
    doNextInstruction : function() {
        var instr = ta.instrQueue.shift();

        if (instr === undefined) {
            console.log("End of the instruction queue.");
            return;
        }

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
    ,
    getRawScript : function () {
        console.log('Getting game script.');
        $.ajax({
            url : "tasTest.txt", //?callback=?",
            dataType : "text",
            success : function (iData, iStatus) {
                console.log('Got game script.');
                ta.rawScript = iData;
            }
        });
    }
}

function onPageLoaded()
{
    ta.getRawScript();

    ta.queueInstruction('say', ['Welcome to TextAdventure (Copyright Albob 2015)', 40, 1000]);
    ta.queueInstruction('clearScreen');
    ta.queueInstruction('say', ['You wake up in a kitchen.']);
    ta.queueInstruction('say', ['The air is filthy.']);
    ta.queueInstruction('say', ['You check your pockets.']);
    ta.queueInstruction('say', ['....', 300]);
    ta.queueInstruction('say', ['Nothing.']);
    ta.doNextInstruction();
}

