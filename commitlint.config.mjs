export default {
  /*
   * Resolve and load @commitlint/config-conventional from node_modules.
   * Referenced packages must be installed
   */
  extends: ['@commitlint/config-conventional'],
  /*
   * Functions that return true if commitlint should ignore the given message.
   */
  ignores: [(message) => message.includes('Merge pull request')],
};
