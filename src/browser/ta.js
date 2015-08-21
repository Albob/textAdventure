/*
 * Albob 2015
 * 
 * TAS, aka Text Adventure Script, is a script language aimed at writing text
 * adventure games.
 * 
 * Each TAS instruction is implemented as a function in the object ta.instructions.
 * Each instruction has control on when to trigger the continuation of the script,
 * by calling ta.doNextInstruction().
 * 
 */

var ta = {
    assert : function (iPredicate, iMessage) {
        if (iMessage === undefined) {
            throw new TypeError("Error: assert expects a valid iMessage");
        }

        if (!iPredicate) {
            throw new TypeError(iMessage);
        }
    }
    ,
    rawScript : '',
    instrQueues : { 'main': [] },
    instrQueueName : 'main',
    instructions : {
        say: function(iMessage, iTextDelayMS, iTextPauseMS) {
            ta.assert(iMessage, "iMessage can't be null");
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
        var queue;

        ta.assert(iName.trim(), 'iName must be non-null and non-empty');
        console.log('Pushing instruction "' + iName + '" with params "' + iParams + '" on queue "' + ta.instrQueueName + '"');
        if (!ta.instrQueues[ta.instrQueueName]) {
            ta.instrQueues[ta.instrQueueName] = [];
        }
        queue = ta.instrQueues[ta.instrQueueName];
        queue.push([iName, iParams]);
    }
    ,
    doNextInstruction : function() {
        var instr = ta.instrQueues[ta.instrQueueName].shift();

        if (instr === undefined) {
            console.log("End of the instruction queue.");
            return;
        }

        var instrName = instr[0];
        var instrParams = instr[1];
        var func = ta.instructions[instrName];

        console.log('Popping instruction "' + instrName + '" with params "' + instrParams + '"');
        // console.log(ta.instrQueues[ta.instrQueueName]);

        if (instrParams && instrParams.length > 0) {
            func.apply(null, instr[1]);
        }
        else {
            func();
        }
    }
    ,
    getRawScript : function (iScriptURI, iOnComplete) {
        ta.assert(iScriptURI != null && iScriptURI.length > 0, "iScriptURI isn't valid");
        ta.assert(iOnComplete !== undefined, 'iOnComplete must be a valid function');
        console.log('Getting game script.');
        $.ajax({
            url : iScriptURI, //?callback=?",
            dataType : "text",
            success : function (iData, iStatus) {
                console.log('Got game script.');
                ta.rawScript = iData;
                iOnComplete();
            }
        });
    }
}

function onPageLoaded(iScriptURI)
{
    ta.getRawScript(iScriptURI, function() {
        var success = ta.parser.parseRawScript();
        
        if (success) {
            ta.doNextInstruction();
        }
    });
}

