var test = require('ava').serial;
var isElevated = require('.');

test('normal', t => {
    t.false(isElevated());
});

test('elevated', t => {
  if (process.platform === 'win32') {
    // TODO
  } else {
    const _ = process.getuid;
    process.getuid = () => 0;
    t.true(isElevated());
    process.getuid = _;
  }
});
