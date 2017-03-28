'use strict';
var isElevated = null;
var tried = false;

module.exports = function() {
  if (!tried) {
    tried = true;
    try {
      isElevated = require('./build/Release/is-elevated');
    } catch (err) {
      console.error(err);
    }
  }

  if (!isElevated) {
    return false;
  }

  var retValue = false;
  try {
    retValue = isElevated.isElevated();
  } catch (err) {
    console.error(err);
  }

  return retValue;
};
