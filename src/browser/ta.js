/*
 * Albob 2015
 * 
 * TAS = Text Adventure Script
 * 
 * TAS is a script language aimed at writing text adventure games.
 * 
 * Each TAS instruction is implemented as a function in the object ta.instructions.
 * Each instruction has control on when to trigger the continuation of the script,
 * by calling ta.doNextInstruction().
 * 
 */


var albob = {
    assert : function (iPredicate, iMessage) {
        if (iMessage === undefined) {
            throw new TypeError("Error: assert expects a valid iMessage");
        }

        if (!iPredicate) {
            throw new TypeError(iMessage);
        }
    }
}

var ta = {
    rawScript : '',
    instrQueue : [],
    instructions : {
        say: function(iMessage, iTextDelayMS, iTextPauseMS) {
            albob.assert(iMessage, "iMessage can't be null");
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
        albob.assert(iName.trim(), 'iName must be non-null and non-empty');
        console.log('Pushing instruction "' + iName + '" with params "' + iParams + '"');
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
    getRawScript : function (iScriptURI, iOnComplete) {
        albob.assert(iScriptURI != null && iScriptURI.length > 0, "iScriptURI isn't valid");
        albob.assert(iOnComplete !== undefined, 'iOnComplete must be a valid function');
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
    ,
    parseRawScript : function () {
        var lines = ta.rawScript.split('\n');
        var lineIndex;
        var line;
        var instr;
        var args;
        var argString;

        console.log("Parsing the raw script.");

        for (lineIndex in lines) {
            line = lines[lineIndex].trim();
            instr = line.split(' ')[0];

            if (instr === undefined || instr.length == 0) {
                continue;
            }

            if (ta.instructions[instr] != undefined) {
                console.log("Found an instruction '" + instr
                    + "' with params '" + line.replace(instr, '').trim() + "'.");
                argString = line.replace(instr, '').trim();

                if (argString) {
                    args = ta.parseArguments(argString);
                    ta.queueInstruction(instr, args);
                }
                else {
                    ta.queueInstruction(instr);
                }
            }
            else {
                console.log("Couldn't find instruction '" + instr + "' at line " + (lineIndex + 1));
                return false;
            }
        }

        return true;
    }
    ,
    parseArguments : function (iArgString) {
        var result = [];
        var begin = 0;
        var end = 0;

        var str = '';
        var nbr = 0;

        albob.assert(iArgString, 'iArgString must be non-null and non-empty');
        while (begin < iArgString.length) {
            if (iArgString[begin] == '"' || iArgString[begin] == "'") {
                end = begin + 1;
                while (end < iArgString.length && iArgString[end] != iArgString[begin]) {
                    end += 1;
                }

                if (iArgString[end] == iArgString[begin]) {
                    str = iArgString.slice(begin + 1, end);
                    result.push(str);
                    begin = end + 1;
                }
                else {
                    throw new SyntaxError('Parsing error: missing " at end of string');
                }
            }
            else if (!isNaN(parseInt(iArgString[begin]))) {
                end = begin + 1;
                while (end < iArgString.length && !isNaN(parseInt(iArgString[end]))) {
                    end += 1;
                }

                nbr = iArgString.slice(begin, end);
                result.push(nbr);
                begin = end;
            }
            else if (iArgString[begin] == ' ') {
                begin += 1;
            }
            else {
                throw new TypeError("At position " + begin + ": " + iArgString[begin]
                    + " is not a valid character");
            }
        }

        return result;
    }
}

function onPageLoaded(iScriptURI)
{
    ta.getRawScript(iScriptURI, function() {
        var success = ta.parseRawScript();
        
        if (success) {
            ta.doNextInstruction();
        }
    });
}

