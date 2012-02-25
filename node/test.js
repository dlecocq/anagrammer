var anagram = require('./build/Release/anagram');

exports.testInsert = function(test) {
	var a = new anagram.Node();
	test.throws(function() { a.insert(5); });
	test.throws(function() { a.insert( ); });
	test.done();
};

exports.testContains = function(test) {
	var a = new anagram.Node();
	
	test.throws(function() { a.contains(5); });
	test.throws(function() { a.contains( ); });
	
	test.equal(a.contains('hello'), false);
	a.insert('hello');
	test.equal(a.contains('hello'), true);
	
	test.done();
}

exports.testDelete = function(test) {
	var a = new anagram.Node();
	
	test.throws(function() { a.delete(5); });
	test.throws(function() { a.delete( ); });
	
	a.insert('hello');
	test.equal(a.contains('hello'), true);
	a.delete('hello');
	test.equal(a.contains('hello'), false);
	
	test.done();
}

exports.testAnagrams = function(test) {
	var a = new anagram.Node();
	
	test.throws(function() { a.anagrams(5); });
	test.throws(function() { a.anagrams( ); });
	
	a.insert('stop');
	a.insert('spot');
	a.insert('post');
	a.insert('pots');
	a.insert('opts');
	a.insert('tops');
	
	test.deepEqual(a.anagrams('ostp'), ['opts', 'post', 'pots', 'spot', 'stop', 'tops']);
	test.done();
}
