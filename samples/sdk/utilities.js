function waitForKeyPress(callback) {
    let readline = require('readline');

    let rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    rl.question("Press any key to continue...", function () {
        rl.close();

        if (typeof callback === 'function') {
            callback();
        }
    });
}


module.exports = exports = {
    waitForKeyPress
};
