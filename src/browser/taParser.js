/*
 * Albob 2015
 * 
 * TAS, aka Text Adventure Script, is a script language aimed at writing text
 * adventure games.
 * 
 */

var ta = ta || {};
ta.parser =  {};

ta.parser.parseRawScript = function () {
    var lines = ta.rawScript.split('\n');
    var lineIndex;
    var line;
    var instr;
    var args;
    var argString;
    var functionName;
    var msg;
    var instrIndex;
    var calledQueue;
    var callingQueue;

    console.log(this);
    console.log("Parsing the raw script.");

    for (lineIndex in lines) {
        line = lines[lineIndex].trim();
        instr = line.split(' ')[0];
        argString = line.replace(instr, '').trim();

        if (instr === undefined || instr.length == 0) {
            continue;
        }

        if (ta.instructions[instr] != undefined) {
            console.log("Found an instruction '" + instr + "' with params '" + argString + "'.");

            if (argString) {
                args = this.parseArguments(argString);
                ta.queueInstruction(instr, args);
            }
            else {
                ta.queueInstruction(instr);
            }
        }
        else if (instr == "def") {
            functionName = this.parseFunctionName(argString);
            ta.assert(ta.instrQueueName == "main", "Can't define a nested function in " + ta.instrQueueName);
            ta.instrQueueName = functionName;
            console.log("Created a function called '" + ta.instrQueueName + "'.");
        }
        else if (instr == "fed") {
            ta.assert(ta.instrQueueName != "main", "Can't close a function in main scope.");
            ta.instrQueueName = "main";
            console.log("Closed a function called '" + ta.instrQueueName + "'.");
        }
        else if (instr == "call") {
            functionName = this.parseFunctionName(argString);
            ta.assert(ta.instrQueues[functionName],
                "Error calling non-existing function: '" + functionName + "'");
            ta.assert(functionName != ta.instrQueueName,
                "Error calling function recursively: '" + functionName + "'");
            calledQueue = ta.instrQueues[functionName];
            callingQueue = ta.instrQueues[ta.instrQueueName];

            console.log("Calling function '" + functionName + "' into '" + ta.instrQueueName + "'");
            for (instrIndex in calledQueue) {
                callingQueue.push(calledQueue[instrIndex]);
            }
        }
        else {
            msg = "Couldn't find instruction '" + instr + "' at line " + (lineIndex + 1);
            console.log(msg);
            alert(msg);
            return false;
        }
    }

    return true;
}

ta.parser.parseArguments = function (iArgString) {
    var result = [];
    var begin = 0;
    var end = 0;

    var str = '';
    var nbr = 0;

    ta.assert(iArgString, 'iArgString must be non-null and non-empty');
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

ta.parser.parseFunctionName = function (iArgString) {
    var args = this.parseArguments(iArgString);
    var functionName = "";

    ta.assert(args.length == 1, "Error in function definition: too many arguments");
    functionName = args[0].trim();
    ta.assert(functionName, "Error in function definition: the name can't be empty.");
    ta.assert(functionName != "main",
        "Error in function definition: the name can't be 'main' because it's a reserved name.");

    return functionName;
}
