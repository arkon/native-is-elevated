var test = require('ava').serial;
var isElevated = require('.');

// Note that 1 of the 2 tests will fail depending on if you're running
// it normally, or with root/admin rights

test('normal', t => {
  t.false(isElevated());
});

test('elevated', t => {
  t.true(isElevated());
});
