'use strict';
var lib = null;
var tried = false;
var returned = false;
var retValue = false;

module.exports = function() {
  if (returned) {
    return retValue;
  }

  if (!tried) {
    // Prevent multiple failed require attempts
    tried = true;
    try {
      lib = require('./build/Release/is-elevated');
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
};
