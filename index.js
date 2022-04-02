'use strict';

let lib = null;
let tried = false;
let returned = false;
let retValue = false;

module.exports = function isElevated() {
  if (process.platform === 'win32') {
    return isElevatedWindows();
  }

  return process.getuid() === 0;
};

function isElevatedWindows() {
  if (returned) {
    return retValue;
  }

  if (!tried) {
    // Prevent multiple failed require attempts
    tried = true;
    try {
      lib = require('./build/Release/iselevated');
    } catch (err) {
      console.error(err);
    }
  }

  if (!lib) {
    return false;
  }

  try {
    // Cache the result for subsequent calls
    returned = true;
    retValue = lib.isElevated();
  } catch (err) {
    console.error(err);
  }

  return retValue;
}
