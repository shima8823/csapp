/*

難しいがプロセッサの仕組みを知る上で良問

回答通り。
すぐ隣のpopqとrrmovqが%rspを使用しようとしているためハザードが起こる。
問題の通りにHCLについて変更した場合、m_valEという古い値が適用してしまうため、別の挙動になってしまう。

*/