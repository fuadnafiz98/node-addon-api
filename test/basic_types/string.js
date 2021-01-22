'use strict';
const buildType = process.config.target_defaults.default_configuration;
const assert = require('assert');

test(require(`../build/${buildType}/binding.node`));
test(require(`../build/${buildType}/binding_noexcept.node`));

function test(binding) {
  const result = 'nodejs';
  assert.ok(binding.basic_types_string.testString(result, 'utf8'));
  assert.ok(binding.basic_types_string.testString(result, 'utf16'));
  assert.ok(binding.basic_types_string.testString(result.substr(0, 4), 'utf8', 4));
  assert.ok(binding.basic_types_string.testString(result.substr(0, 4), 'utf16', 4));

  const tempString = binding.basic_types_string.newString('utf8');
  assert.strictEqual(tempString, result);
  assert.ok(binding.basic_types_string.testString(result, 'utf8'));
  assert.ok(binding.basic_types_string.testString(result, 'utf16'));
  assert.ok(binding.basic_types_string.testString(result.substr(0, 4), 'utf8', 4));
  assert.ok(binding.basic_types_string.testString(result.substr(0, 4), 'utf16', 4));

  const tempString2 = binding.basic_types_string.newString('utf16');
  assert.strictEqual(tempString2, result);
  assert.ok(binding.basic_types_string.testString(result, 'utf8'));
  assert.ok(binding.basic_types_string.testString(result, 'utf16'));
  assert.ok(binding.basic_types_string.testString(result.substr(0, 4), 'utf8', 4));
  assert.ok(binding.basic_types_string.testString(result.substr(0, 4), 'utf16', 4));
}